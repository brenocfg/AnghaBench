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
struct btrfs_mapping_tree {int /*<<< orphan*/  map_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  extent_map_tree_init (int /*<<< orphan*/ *) ; 

void btrfs_mapping_init(struct btrfs_mapping_tree *tree)
{
	extent_map_tree_init(&tree->map_tree);
}