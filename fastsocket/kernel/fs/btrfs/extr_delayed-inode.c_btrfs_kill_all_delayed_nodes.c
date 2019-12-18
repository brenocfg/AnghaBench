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
typedef  scalar_t__ u64 ;
struct btrfs_root {int /*<<< orphan*/  inode_lock; int /*<<< orphan*/  delayed_nodes_tree; } ;
struct btrfs_delayed_node {int /*<<< orphan*/  refs; scalar_t__ inode_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct btrfs_delayed_node**) ; 
 int /*<<< orphan*/  __btrfs_kill_delayed_node (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_release_delayed_node (struct btrfs_delayed_node*) ; 
 int radix_tree_gang_lookup (int /*<<< orphan*/ *,void**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_kill_all_delayed_nodes(struct btrfs_root *root)
{
	u64 inode_id = 0;
	struct btrfs_delayed_node *delayed_nodes[8];
	int i, n;

	while (1) {
		spin_lock(&root->inode_lock);
		n = radix_tree_gang_lookup(&root->delayed_nodes_tree,
					   (void **)delayed_nodes, inode_id,
					   ARRAY_SIZE(delayed_nodes));
		if (!n) {
			spin_unlock(&root->inode_lock);
			break;
		}

		inode_id = delayed_nodes[n - 1]->inode_id + 1;

		for (i = 0; i < n; i++)
			atomic_inc(&delayed_nodes[i]->refs);
		spin_unlock(&root->inode_lock);

		for (i = 0; i < n; i++) {
			__btrfs_kill_delayed_node(delayed_nodes[i]);
			btrfs_release_delayed_node(delayed_nodes[i]);
		}
	}
}