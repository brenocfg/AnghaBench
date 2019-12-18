#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  TYPE_2__* splay_tree ;
struct TYPE_7__ {int (* comp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* root; } ;
struct TYPE_6__ {struct TYPE_6__* left; struct TYPE_6__* right; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  splay_tree_splay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

splay_tree_node
splay_tree_successor (splay_tree sp, splay_tree_key key)
{
  int comparison;
  splay_tree_node node;

  /* If the tree is empty, there is certainly no successor.  */
  if (!sp->root)
    return NULL;

  /* Splay the tree around KEY.  That will leave either the KEY
     itself, its predecessor, or its successor at the root.  */
  splay_tree_splay (sp, key);
  comparison = (*sp->comp)(sp->root->key, key);

  /* If the successor is at the root, just return it.  */
  if (comparison > 0)
    return sp->root;

  /* Otherwise, find the leftmost element of the right subtree.  */
  node = sp->root->right;
  if (node)
    while (node->left)
      node = node->left;

  return node;
}