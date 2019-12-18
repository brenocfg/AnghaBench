#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mfsplay_tree_node ;
struct TYPE_4__ {struct TYPE_4__* right; struct TYPE_4__* left; } ;

/* Variables and functions */

__attribute__((used)) static mfsplay_tree_node
mfsplay_tree_rebalance_helper2 (mfsplay_tree_node * array, unsigned low,
                              unsigned high)
{
  unsigned middle = low + (high - low) / 2;
  mfsplay_tree_node n = array[middle];

  /* Note that since we're producing a balanced binary tree, it is not a problem
     that this function is recursive.  */
  if (low + 1 <= middle)
    n->left = mfsplay_tree_rebalance_helper2 (array, low, middle - 1);
  else
    n->left = NULL;

  if (middle + 1 <= high)
    n->right = mfsplay_tree_rebalance_helper2 (array, middle + 1, high);
  else
    n->right = NULL;

  return n;
}