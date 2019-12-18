#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mfsplay_tree_node ;
typedef  scalar_t__ mfsplay_tree_key ;
typedef  TYPE_2__* mfsplay_tree ;
struct TYPE_9__ {scalar_t__ depth; scalar_t__ max_depth; int rebalance_p; } ;
struct TYPE_8__ {scalar_t__ key; struct TYPE_8__* right; struct TYPE_8__* left; } ;

/* Variables and functions */

__attribute__((used)) static mfsplay_tree_node
mfsplay_tree_splay_helper (mfsplay_tree sp,
                         mfsplay_tree_key key,
                         mfsplay_tree_node * node,
                         mfsplay_tree_node * parent,
                         mfsplay_tree_node * grandparent)
{
  mfsplay_tree_node *next;
  mfsplay_tree_node n;
  int comparison;

  n = *node;

  if (!n)
    return *parent;

  comparison = ((key > n->key) ? 1 : ((key < n->key) ? -1 : 0));

  if (comparison == 0)
    /* We've found the target.  */
    next = 0;
  else if (comparison < 0)
    /* The target is to the left.  */
    next = &n->left;
  else
    /* The target is to the right.  */
    next = &n->right;

  if (next)
    {
      /* Check whether our recursion depth is too high.  Abort this search,
         and signal that a rebalance is required to continue.  */
      if (sp->depth > sp->max_depth)
        {
          sp->rebalance_p = 1;
          return n;
         }

      /* Continue down the tree.  */
      sp->depth ++;
      n = mfsplay_tree_splay_helper (sp, key, next, node, parent);
      sp->depth --;

      /* The recursive call will change the place to which NODE
         points.  */
      if (*node != n || sp->rebalance_p)
        return n;
    }

  if (!parent)
    /* NODE is the root.  We are done.  */
    return n;

  /* First, handle the case where there is no grandparent (i.e.,
   *PARENT is the root of the tree.)  */
  if (!grandparent)
    {
      if (n == (*parent)->left)
        {
          *node = n->right;
          n->right = *parent;
        }
      else
        {
          *node = n->left;
          n->left = *parent;
        }
      *parent = n;
      return n;
    }

  /* Next handle the cases where both N and *PARENT are left children,
     or where both are right children.  */
  if (n == (*parent)->left && *parent == (*grandparent)->left)
    {
      mfsplay_tree_node p = *parent;

      (*grandparent)->left = p->right;
      p->right = *grandparent;
      p->left = n->right;
      n->right = p;
      *grandparent = n;
      return n;
    }
  else if (n == (*parent)->right && *parent == (*grandparent)->right)
    {
      mfsplay_tree_node p = *parent;

      (*grandparent)->right = p->left;
      p->left = *grandparent;
      p->right = n->left;
      n->left = p;
      *grandparent = n;
      return n;
    }

  /* Finally, deal with the case where N is a left child, but *PARENT
     is a right child, or vice versa.  */
  if (n == (*parent)->left)
    {
      (*parent)->left = n->right;
      n->right = *parent;
      (*grandparent)->right = n->left;
      n->left = *grandparent;
      *grandparent = n;
      return n;
    }
  else
    {
      (*parent)->right = n->left;
      n->left = *parent;
      (*grandparent)->left = n->right;
      n->right = *grandparent;
      *grandparent = n;
      return n;
    }
}