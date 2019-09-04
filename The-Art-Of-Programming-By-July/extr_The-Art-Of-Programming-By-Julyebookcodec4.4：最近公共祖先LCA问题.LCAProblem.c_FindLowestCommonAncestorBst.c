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

Node* FindLowestCommonAncestorBst(Node* root, Node* u, Node* v)
{
    
    // 参数检查
    if (NULL == root || NULL == u || NULL == v) {
        fprintf(stderr, "Wrong input data! Exit!");
        return NULL;
    }
    
     if (root == u || root == v) {
         return root;
     }
     if (u == v) {
         return u;
     }
    
    //这段必须放在参数检查之后，不然有空指针异常
    
    int left_value = u->value;    
    int right_value = v->value;    
    Node* parent_node = NULL;
    Node* cur_node = root;
    

    // 调整左右节点值到正确
    if (left_value > right_value) {    
        swap(left_value, right_value);
    }    

    while (cur_node) {
        // 如果cur_node的值小于u、v的值，说明LCA节点应该在其右子树中
        if (cur_node->value < left_value) {    
            parent_node = cur_node;    
            cur_node = cur_node->right;    
        } else if (cur_node->value > right_value) {    
            // 如果cur_node的值大于u、v的值，则应该查询其左子树
            parent_node = cur_node;    
            cur_node = cur_node->left;    
        } else if (cur_node->value == left_value || cur_node->value == right_value) {
            // 找到节点u或者v处，说明其父节点即为所求
            return parent_node;
        } else {
            // 现在cur_node的值处于u和v的值之间，显然即为所求
            return cur_node;
        }    
    } 
    
    // 数据有误，找不到任何的LCA节点
    return NULL;
}