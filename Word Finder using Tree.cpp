#include <iostream> //2019504 Syed Nazim Shah
#include <string>   //2019005 Hadi Sohail
#include <fstream>
using namespace std;

struct node {
  string data;
  node * left;
  node * right;
  int height;
};

class avl {
  public:
    node * root;
  avl() {
    root = NULL;
  }

  int max(int a, int b) {
    if (a < b) return b;
    else return a;
  }

  int height(node * temp) {
    int h = 0;
    if (temp != NULL) {
      int l_height = height(temp -> left);
      int r_height = height(temp -> right);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
    }
    return h;
  }
  int difference(node * temp) {
    int l_height = height(temp -> left);
    int r_height = height(temp -> right);
    int b_factor = l_height - r_height;
    return b_factor;
  }
  node * rrrotat(node * parent) {
    node * temp;
    temp = parent -> right;
    parent -> right = temp -> left;
    temp -> left = parent;
    return temp;
  }
  node * llrotat(node * parent) {
    node * temp;
    temp = parent -> left;
    parent -> left = temp -> right;
    temp -> right = parent;
    return temp;
  }
  node * lrrotat(node * parent) {
    node * temp;
    temp = parent -> left;
    parent -> left = rrrotat(temp);
    return llrotat(parent);
  }
  node * rlrotat(node * parent) {
    node * temp;
    temp = parent -> right;
    parent -> right = llrotat(temp);
    return rrrotat(parent);
  }
  node * balance(node * temp) {
    int balfactor = difference(temp);
    if (balfactor > 1) {
      if (difference(temp -> left) > 0)
        temp = llrotat(temp);
      else
        temp = lrrotat(temp);
    } else if (balfactor < -1) {
      if (difference(temp -> right) > 0)
        temp = rlrotat(temp);
      else
        temp = rrrotat(temp);
    }
    return temp;
  }
  node * insert(node * r, string value) {
    if (r == NULL) {
      r = new node;
      r -> data = value;
      r -> left = NULL;
      r -> right = NULL;
      return r;
    } else if (value < r -> data) {
      r -> left = insert(r -> left, value);
      r = balance(r);
    } else if (value >= r -> data) {
      r -> right = insert(r -> right, value);
      r = balance(r);
    }
    return r;
  }
  string searchword(node * temp, string value) {
    if (temp == NULL) return "";
    else if (value == temp -> data)
      return value;
    else if (value < temp -> data)
      return searchword(temp -> left, value);
    else if (value > temp -> data)
      return searchword(temp -> right, value);
  }
};

class puzzle {
  public:
    avl tree;
  string crossword[7];
  puzzle() {
    crossword[0] = {"dogxbxxxnoon"};
    crossword[1] = {"rhellotherex"};
    crossword[2] = {"okciuqbrownm"};
    crossword[3] = {"wxwgexlxhjij"};
    crossword[4] = {"oozokvuxdrow"};
    crossword[5] = {"rlxdrxextxja"};
    crossword[6] = {"drowblonkgod"};
    //adding words from library to avl tree
    string temp;
    ifstream myfile;
    myfile.open("wordlibrary.txt");
    while (getline(myfile, temp)) {
      tree.root = tree.insert(tree.root, temp);
    }
  }

  void gen_comp_disp() {
  	ofstream myfile;
    myfile.open("savewords.txt");
    for (int i = 0; i < 7; i++) {
      for (int j = 0; j < 12; j++) {
        string temp = ""; // hleft
        for (int n = j; n >= 0; n--) {
          temp += crossword[i][n];
          cout << tree.searchword(tree.root, temp);
          if (tree.searchword(tree.root, temp) != "") {cout << endl; myfile<<temp<<" "<<"("<<i<<","<<j<<")"<<"("<<i<<","<<n<<")"<<endl;}
        }
        temp = ""; // hright
        for (int n = j; n <= 12; n++) {
          temp += crossword[i][n];
          cout << tree.searchword(tree.root, temp);
          if (tree.searchword(tree.root, temp) != "") {cout << endl; myfile<<temp<<" "<<"("<<i<<","<<j<<")"<<"("<<i<<","<<n<<")"<<endl;}
        }
        temp = "";
        for (int m = i; m >= 0; m--) { //v up
          temp += crossword[m][j];
          cout << tree.searchword(tree.root, temp);
          if (tree.searchword(tree.root, temp) != "") {cout << endl; myfile<<temp<<" "<<"("<<i<<","<<j<<")"<<"("<<m<<","<<j<<")"<<endl;}
        }
        temp = "";
        for (int m = i; m < 7; m++) { //v down
          temp += crossword[m][j];
          cout << tree.searchword(tree.root, temp);
          if (tree.searchword(tree.root, temp) != "") {cout << endl; myfile<<temp<<" "<<"("<<i<<","<<j<<")"<<"("<<m<<","<<j<<")"<<endl;}
        }
        temp = "";
        for (int m = i, n = j; m >= 0 && n >= 0; m--, n--) { // top left
          temp += crossword[m][n];
          cout << tree.searchword(tree.root, temp);
          if (tree.searchword(tree.root, temp) != "") {cout << endl; myfile<<temp<<" "<<"("<<i<<","<<j<<")"<<"("<<m<<","<<n<<")"<<endl;}
        }
        temp = "";
        for (int m = i, n = j; m < 7 && n < 12; m++, n++) { // bottom right
          temp += crossword[m][n];
          cout << tree.searchword(tree.root, temp);
          if (tree.searchword(tree.root, temp) != "") {cout << endl; myfile<<temp<<" "<<"("<<i<<","<<j<<")"<<"("<<m<<","<<n<<")"<<endl;}
        }
        temp = "";
        for (int m = i, n = j; m >= 0 && n < 12; m--, n++) { // top right
          temp += crossword[m][n];
          cout << tree.searchword(tree.root, temp);
          if (tree.searchword(tree.root, temp) != "") {cout << endl; myfile<<temp<<" "<<"("<<i<<","<<j<<")"<<"("<<m<<","<<n<<")"<<endl;}
        }
        temp = "";
        for (int m = i, n = j; m < 7 && n >= 0; m++, n--) { // bottom left
          temp += crossword[m][n];
          cout << tree.searchword(tree.root, temp);
          if (tree.searchword(tree.root, temp) != "") {cout << endl; myfile<<temp<<" "<<"("<<i<<","<<j<<")"<<"("<<m<<","<<n<<")"<<endl;}
          
        }
      }
    }
  }
};

int main() {
  puzzle puz;
  puz.gen_comp_disp();
  return 0;
}
