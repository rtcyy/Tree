//伸展树（不需要 AVL树的严格平衡）

#include <stdio.h>
#include <stdlib.h>

/*
Tree* createNode(int data)          //创建一个新节点
Tree* leftRotate(Tree* x)           //左旋
Tree* rightRotate(Tree* y)          //右旋
Tree* splay(Tree* root,int data)    //伸展
Tree* insert(Tree* root,int data)   //插入元素
Tree* remove(Tree* root,int data)   //删除元素
void inOrderTraversal(Tree* root)   //中序遍历
*/

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}Tree;

Tree* createNode(int data){
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//左旋
Tree* leftRotate(Tree* x){
    Tree* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

//右旋
Tree* rightRotate(Tree* y){
    Tree* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

//伸展
Tree* splay(Tree* root,int data){
    Tree* head = (Tree*)malloc(sizeof(Tree));     //头结点，有左右子树，左子树用来接收最后接到 root 的右子树，右子树用来接收最后接到 root 的左子树
    head->left = NULL;
    head->right = NULL;
    
    Tree* leftTreeMax;  // 最后接到 root 的左子树中的最大值
    Tree* rightTreeMin; // 最后接到 root 的右子树中的最小值
    leftTreeMax = head;
    rightTreeMin = head; 

    //当值未找到
    while(data != root->data){
        if(data < root->data){
            //左子树为空，退出循环
            if(root->left == NULL){
                break;
            }
            //左左
            if(data < root->left->data){
                root = rightRotate(root);
            }
            rightTreeMin->left = root;  //添加给右子树
            rightTreeMin = root;        //更新rightTreeMin
            root = root->left;          //更新root
        }
        if(data > root->data){
            //右子树为空，退出循环
            if(root->right == NULL){
                break;
            }
            //右右
            if(data > root->right->data){
                root = leftRotate(root);
            }
            leftTreeMax->right = root;  //添加给左子树
            leftTreeMax = root;         //更新leftTreeMax
            root = root->right;         //更新root
        }
    }
    //连接
    leftTreeMax->right = root->left;
    rightTreeMin->left = root->right;
    root->left = head->right;
    root->right = head->left;

    return root;
}

//插入元素
Tree* insert(Tree* root,int data){
    Tree* newNode = createNode(data);
    if(root == NULL) root = newNode;
    else{
        root = splay(root,data);
        if(data < root->data){
            newNode->left = root->left;
            newNode->right = root;
            root->left = NULL;
            root = newNode;
        }
        if(data > root->data){
            newNode->right = root->right;
            newNode->left = root;
            root->right = NULL;
            root = newNode;
        }
        else{
            free(newNode);
        }
    }
    return root;
}

//删除元素
Tree* remove(Tree* root,int data){
    Tree* newNode;
    root = splay(root,data);
    if(data == root->data){
        if(root->left == NULL){
            newNode = root->right;
        }else{
            newNode = splay(root->left,data);
            newNode->right = root->right;
        }
        free(root);
    }
    return newNode;
}

//中序遍历
void inOrderTraversal(Tree* root){
    if(root != NULL){
        inOrderTraversal(root->left);
        printf("%d ",root->data);
        inOrderTraversal(root->right);
    }
}

int main(){
    Tree* t = createNode(12);
    t->left = createNode(5);
    t->right = createNode(25);
    t->right->right = createNode(30);
    t->right->left = createNode(20);
    t->right->left->right = createNode(24);
    t->right->left->left = createNode(15);
    t->right->left->left->right = createNode(18);
    t->right->left->left->left = createNode(13);
    t->right->left->left->right->left = createNode(16);
    t = insert(t,19);
    inOrderTraversal(t);
    printf("\n");
    // t = remove(t,19);
    // inOrderTraversal(t);
    // printf("\n");
    // t = remove(t,18);
    // inOrderTraversal(t);
    // printf("\n");

    return 0;
}