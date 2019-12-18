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
struct btrfs_root {int dummy; } ;
struct btrfs_delayed_root {int dummy; } ;
struct btrfs_delayed_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __btrfs_kill_delayed_node (struct btrfs_delayed_node*) ; 
 struct btrfs_delayed_node* btrfs_first_delayed_node (struct btrfs_delayed_root*) ; 
 struct btrfs_delayed_root* btrfs_get_delayed_root (struct btrfs_root*) ; 
 struct btrfs_delayed_node* btrfs_next_delayed_node (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  btrfs_release_delayed_node (struct btrfs_delayed_node*) ; 

void btrfs_destroy_delayed_inodes(struct btrfs_root *root)
{
	struct btrfs_delayed_root *delayed_root;
	struct btrfs_delayed_node *curr_node, *prev_node;

	delayed_root = btrfs_get_delayed_root(root);

	curr_node = btrfs_first_delayed_node(delayed_root);
	while (curr_node) {
		__btrfs_kill_delayed_node(curr_node);

		prev_node = curr_node;
		curr_node = btrfs_next_delayed_node(curr_node);
		btrfs_release_delayed_node(prev_node);
	}
}