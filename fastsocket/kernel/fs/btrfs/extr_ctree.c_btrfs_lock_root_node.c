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
struct extent_buffer {int dummy; } ;
struct btrfs_root {struct extent_buffer* node; } ;

/* Variables and functions */
 struct extent_buffer* btrfs_root_node (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_tree_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_unlock (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 

struct extent_buffer *btrfs_lock_root_node(struct btrfs_root *root)
{
	struct extent_buffer *eb;

	while (1) {
		eb = btrfs_root_node(root);
		btrfs_tree_lock(eb);
		if (eb == root->node)
			break;
		btrfs_tree_unlock(eb);
		free_extent_buffer(eb);
	}
	return eb;
}