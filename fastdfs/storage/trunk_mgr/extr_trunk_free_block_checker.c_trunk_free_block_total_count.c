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
 int /*<<< orphan*/  avl_tree_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  block_tree_count_walk_callback ; 
 int /*<<< orphan*/  tree_info_by_id ; 

int trunk_free_block_total_count()
{
	int count;
	count = 0;
	avl_tree_walk(&tree_info_by_id, block_tree_count_walk_callback, &count);
	return count;
}