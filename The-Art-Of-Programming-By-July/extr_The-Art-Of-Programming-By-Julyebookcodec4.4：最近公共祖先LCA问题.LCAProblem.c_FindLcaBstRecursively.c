#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int value; struct TYPE_6__* left; struct TYPE_6__* right; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  swap (int,int) ; 

Node* FindLcaBstRecursively(Node* root, Node* u, Node* v)
{
    // 参数检查
    // NOTICE:特别包含了u、v即是root节点的情况，此时应该返回NULL
    if (NULL == root || NULL == u || NULL == v
        || root == u || root == v || u == v) {
        fprintf(stderr, "Wrong input data: Arguments check failed! Exit!");
        return NULL;
    }
    
    int left_value = u->value;    
    int right_value = v->value;    

    // 调整左右节点值到正确
    if (left_value > right_value) {    
        swap(left_value, right_value);
    }    
    
    // 判断当前节点是否为所求LCA节点
    // 情形1：u、v分别在root的左右子树上
    if (root->value > left_value
        && root->value < right_value) {
        return root;
    }

    // 情形2：u、v都在root的同一棵子树且u、v有一个节点是root的子节点
    if (root->right == u || root->right == v
        || root->left == u || root->left == v) {
        return root;
    }

    // 当前节点不是所求LCA，则递归返回左右子树的LCA节点
    if (root->value < left_value) { // 查找右子树
        return FindLcaBstRecursively(root->right, u, v);
    } else if (root->value > right_value) { // 查找左子树
        return FindLcaBstRecursively(root->left, u, v);
    }
}