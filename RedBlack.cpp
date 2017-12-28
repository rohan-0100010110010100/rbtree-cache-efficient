/*
Author: Rohan Verma
Problem: Redblack DS ( LLRB - Left Leaning RedBlack tree )
Hint : Use your Brains not B0obs
*/


#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <jemalloc/jemalloc.h>


template <class T>
class Redblack{
public:
  typedef struct Redblacknode{
    T val;
    int col;
    struct Redblacknode* parent;
    struct Redblacknode* nl;
    struct Redblacknode* nr;
  }Node;
  void printTree(Node* n);
  Node* base;
  Node *nil;
  enum{R,B};
  Redblack(T val){
    nil= (Node*)malloc(sizeof(Node));
    base = (Node*)malloc(sizeof(Node));

    nil->col=B;
    nil->nl=nil;
    nil->nr=nil;    nil->parent=nil;
    base->col=B;
    base->parent=nil;
    base->nl=nil;
    base->nr=nil;
    base->val = val;
  }
  ~Redblack(){
    //Memory free
   // Node* n=base;
    
    free(base);
    free(nil);
  }
  void insert(T key);
  void remove(T key);

  int search(T key)const;
   int findmax() const;
  int findmin() const;
private:
 void left_rotate(Node* n);
 void right_rotate(Node* n);
};




template <class T>
void Redblack<T>::printTree(Node* n){

if( n != nil ){
std::cout << n->val <<'\t'<< n->col<<'\t'<< n->parent->val<<'\n';
if(n->nl!=nil)
printTree( n->nl );



if(n->nr!=nil)
printTree( n->nr );
}

}

template <class T>
void Redblack<T>::left_rotate(Node* n){

Node * y;
    y= n->nr;
n->nr=y->nl;
if (y->nl != nil)
    y->nl->parent= n;
  y->parent = n->parent;

if(n->parent==nil)
   base=y;
 else if(n == n->parent->nl)
    n->parent->nl=y;
  else
    n->parent->nr=y;

  y->nl = n;
    n->parent = y;
  }






template <class T>
void Redblack<T>::right_rotate(Node* n){

 Node* x;
 x = n->nl;
 n->nl=x->nr;
 if(x->nr!=nil)
  x->nr->parent = n;

x->parent = n->parent;
if(n->parent==nil)
   base=x;
else if(n==n->parent->nr)
n->parent->nr=x;
else
n->parent->nl=x;
x->nr=n;
n->parent=x;
}

template <class T>
void Redblack<T>::remove(T key){
  Node* w = base;
  Node* y = nil;

  while(w->val!=key){
      y = w;
    if(key>w->val)
    w = w->nr;
    else
    w= w->nl;
  }





}

template <class T>
void Redblack<T>::insert(T key){
  Node* w = base;
  Node* y = nil;
  Node* x=(Node*)malloc(sizeof(Node));

  while(w!=nil){
      y = w;
    if(key>w->val)
    w = w->nr;
    else
    w= w->nl;
  }
  x->parent = y;
  if(y==nil)
    base = x;
  else if(key < y->val)
  y->nl=x;
  else
  y->nr=x;

  x->col=R;
  x->val=key;
  x->nr=nil;
  x->nl=nil;

  while ( (x != base) && (x->parent->col == R) ) {
      if ( x->parent == x->parent->parent->nl ) {
          /* If x's parent is a left, y is x's right 'uncle' */
          y = x->parent->parent->nr;
          if ( y->col == R ) {
              /* case 1 - change the cols */
              x->parent->col = B;
              y->col = B;
              x->parent->parent->col = R;
              /* Move x up the tree */
              x = x->parent->parent;
              }
          else {
              /* y is a black node */
              if ( x == x->parent->nr ) {
                  /* and x is to the right */
                  /* case 2 - move x up and rotate */
                  x = x->parent;
                  left_rotate(x);
                  }
              /* case 3 */
              x->parent->col = B;
              x->parent->parent->col = R;
              right_rotate(x->parent->parent);
              }
          }
      else {
        y = x->parent->parent->nl;
        if ( y->col == R ) {
            /* case 1 - change the cols */
            x->parent->col = B;
            y->col = B;
            x->parent->parent->col = R;
            /* Move x up the tree */
            x = x->parent->parent;
            }
        else {
            /* y is a black node */
            if ( x == x->parent->nl ) {
                /* and x is to the right */
                /* case 2 - move x up and rotate */
                x = x->parent;
                right_rotate( x );
                }
            /* case 3 */
            x->parent->col = B;
            x->parent->parent->col = R;
            left_rotate( x->parent->parent );
            }
          }
      }
   /* col the root black */
  base->col = B;
}

Redblack<int> t_tree(0);




int main(){

  for(int x = 1 ; x<100000;++x)
    t_tree.insert(x);


t_tree.printTree(t_tree.base);



}
