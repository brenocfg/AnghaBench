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
struct splay_tree_node_s {int dummy; } ;
typedef  void* splay_tree_value ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  TYPE_2__* splay_tree ;
struct TYPE_7__ {int (* comp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* root; int /*<<< orphan*/  allocate_data; scalar_t__ (* allocate ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* delete_value ) (void*) ;} ;
struct TYPE_6__ {struct TYPE_6__* left; struct TYPE_6__* right; void* value; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  splay_tree_splay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 scalar_t__ stub3 (int,int /*<<< orphan*/ ) ; 

splay_tree_node
splay_tree_insert (splay_tree sp, splay_tree_key key, splay_tree_value value)
{
  int comparison = 0;

  splay_tree_splay (sp, key);

  if (sp->root)
    comparison = (*sp->comp)(sp->root->key, key);

  if (sp->root && comparison == 0)
    {
      /* If the root of the tree already has the indicated KEY, just
	 replace the value with VALUE.  */
      if (sp->delete_value)
	(*sp->delete_value)(sp->root->value);
      sp->root->value = value;
    } 
  else 
    {
      /* Create a new node, and insert it at the root.  */
      splay_tree_node node;
      
      node = ((splay_tree_node)
              (*sp->allocate) (sizeof (struct splay_tree_node_s),
                               sp->allocate_data));
      node->key = key;
      node->value = value;
      
      if (!sp->root)
	node->left = node->right = 0;
      else if (comparison < 0)
	{
	  node->left = sp->root;
	  node->right = node->left->right;
	  node->left->right = 0;
	}
      else
	{
	  node->right = sp->root;
	  node->left = node->right->left;
	  node->right->left = 0;
	}

      sp->root = node;
    }

  return sp->root;
}