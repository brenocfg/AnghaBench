#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mfsplay_tree_node_s {int dummy; } ;
typedef  void* mfsplay_tree_value ;
typedef  TYPE_1__* mfsplay_tree_node ;
typedef  scalar_t__ mfsplay_tree_key ;
typedef  TYPE_2__* mfsplay_tree ;
struct TYPE_8__ {TYPE_1__* root; scalar_t__ last_splayed_key_p; int /*<<< orphan*/  num_keys; } ;
struct TYPE_7__ {scalar_t__ key; struct TYPE_7__* left; struct TYPE_7__* right; void* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfsplay_tree_splay (TYPE_2__*,scalar_t__) ; 
 TYPE_1__* mfsplay_tree_xmalloc (int) ; 

__attribute__((used)) static mfsplay_tree_node
mfsplay_tree_insert (mfsplay_tree sp, mfsplay_tree_key key, mfsplay_tree_value value)
{
  int comparison = 0;

  mfsplay_tree_splay (sp, key);

  if (sp->root)
    comparison = ((sp->root->key > key) ? 1 :
                  ((sp->root->key < key) ? -1 : 0));

  if (sp->root && comparison == 0)
    {
      /* If the root of the tree already has the indicated KEY, just
         replace the value with VALUE.  */
      sp->root->value = value;
    }
  else
    {
      /* Create a new node, and insert it at the root.  */
      mfsplay_tree_node node;

      node = mfsplay_tree_xmalloc (sizeof (struct mfsplay_tree_node_s));
      node->key = key;
      node->value = value;
      sp->num_keys++;
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
      sp->last_splayed_key_p = 0;
    }

  return sp->root;
}