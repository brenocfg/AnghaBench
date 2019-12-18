#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int avl_tree_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_info_by_id ; 

int trunk_free_block_tree_node_count()
{
	return avl_tree_count(&tree_info_by_id);
}