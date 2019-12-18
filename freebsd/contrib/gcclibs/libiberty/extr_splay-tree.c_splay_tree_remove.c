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
struct TYPE_7__ {scalar_t__ (* comp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* root; int /*<<< orphan*/  allocate_data; int /*<<< orphan*/  (* deallocate ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* delete_value ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {struct TYPE_6__* right; int /*<<< orphan*/  value; struct TYPE_6__* left; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  splay_tree_splay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
splay_tree_remove (splay_tree sp, splay_tree_key key)
{
  splay_tree_splay (sp, key);

  if (sp->root && (*sp->comp) (sp->root->key, key) == 0)
    {
      splay_tree_node left, right;

      left = sp->root->left;
      right = sp->root->right;

      /* Delete the root node itself.  */
      if (sp->delete_value)
	(*sp->delete_value) (sp->root->value);
      (*sp->deallocate) (sp->root, sp->allocate_data);

      /* One of the children is now the root.  Doesn't matter much
	 which, so long as we preserve the properties of the tree.  */
      if (left)
	{
	  sp->root = left;

	  /* If there was a right child as well, hang it off the 
	     right-most leaf of the left child.  */
	  if (right)
	    {
	      while (left->right)
		left = left->right;
	      left->right = right;
	    }
	}
      else
	sp->root = right;
    }
}