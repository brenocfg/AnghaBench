#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  inode_lock; int /*<<< orphan*/  inode_tree; TYPE_1__* fs_info; int /*<<< orphan*/  root_item; } ;
struct TYPE_4__ {int /*<<< orphan*/  rb_node; struct btrfs_root* root; } ;
struct TYPE_3__ {int /*<<< orphan*/  subvol_srcu; struct btrfs_root* tree_root; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_add_dead_root (struct btrfs_root*) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inode_tree_del(struct inode *inode)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int empty = 0;

	spin_lock(&root->inode_lock);
	if (!RB_EMPTY_NODE(&BTRFS_I(inode)->rb_node)) {
		rb_erase(&BTRFS_I(inode)->rb_node, &root->inode_tree);
		RB_CLEAR_NODE(&BTRFS_I(inode)->rb_node);
		empty = RB_EMPTY_ROOT(&root->inode_tree);
	}
	spin_unlock(&root->inode_lock);

	/*
	 * Free space cache has inodes in the tree root, but the tree root has a
	 * root_refs of 0, so this could end up dropping the tree root as a
	 * snapshot, so we need the extra !root->fs_info->tree_root check to
	 * make sure we don't drop it.
	 */
	if (empty && btrfs_root_refs(&root->root_item) == 0 &&
	    root != root->fs_info->tree_root) {
		synchronize_srcu(&root->fs_info->subvol_srcu);
		spin_lock(&root->inode_lock);
		empty = RB_EMPTY_ROOT(&root->inode_tree);
		spin_unlock(&root->inode_lock);
		if (empty)
			btrfs_add_dead_root(root);
	}
}