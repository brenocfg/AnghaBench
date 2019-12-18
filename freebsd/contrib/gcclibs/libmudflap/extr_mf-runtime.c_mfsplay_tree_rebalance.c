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
typedef  int /*<<< orphan*/  mfsplay_tree_node ;
typedef  TYPE_1__* mfsplay_tree ;
struct TYPE_4__ {int num_keys; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  mfsplay_tree_foreach (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mfsplay_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfsplay_tree_rebalance_helper1 ; 
 int /*<<< orphan*/  mfsplay_tree_rebalance_helper2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mfsplay_tree_xmalloc (int) ; 

__attribute__((used)) static void
mfsplay_tree_rebalance (mfsplay_tree sp)
{
  mfsplay_tree_node *all_nodes, *all_nodes_1;

  if (sp->num_keys <= 2)
    return;

  all_nodes = mfsplay_tree_xmalloc (sizeof (mfsplay_tree_node) * sp->num_keys);

  /* Traverse all nodes to copy their addresses into this array.  */
  all_nodes_1 = all_nodes;
  mfsplay_tree_foreach (sp, mfsplay_tree_rebalance_helper1,
                      (void *) &all_nodes_1);

  /* Relink all the nodes.  */
  sp->root = mfsplay_tree_rebalance_helper2 (all_nodes, 0, sp->num_keys - 1);

  mfsplay_tree_free (all_nodes);
}