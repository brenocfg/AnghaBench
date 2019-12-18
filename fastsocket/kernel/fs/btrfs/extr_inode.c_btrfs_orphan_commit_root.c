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
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {scalar_t__ orphan_cleanup_state; scalar_t__ orphan_item_inserted; TYPE_2__ root_key; TYPE_1__* fs_info; int /*<<< orphan*/  root_item; int /*<<< orphan*/  orphan_lock; struct btrfs_block_rsv* orphan_block_rsv; int /*<<< orphan*/  orphan_inodes; } ;
struct btrfs_block_rsv {scalar_t__ size; } ;
struct TYPE_3__ {int /*<<< orphan*/  tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ ORPHAN_CLEANUP_DONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int btrfs_del_orphan_item (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_free_block_rsv (struct btrfs_root*,struct btrfs_block_rsv*) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_orphan_commit_root(struct btrfs_trans_handle *trans,
			      struct btrfs_root *root)
{
	struct btrfs_block_rsv *block_rsv;
	int ret;

	if (atomic_read(&root->orphan_inodes) ||
	    root->orphan_cleanup_state != ORPHAN_CLEANUP_DONE)
		return;

	spin_lock(&root->orphan_lock);
	if (atomic_read(&root->orphan_inodes)) {
		spin_unlock(&root->orphan_lock);
		return;
	}

	if (root->orphan_cleanup_state != ORPHAN_CLEANUP_DONE) {
		spin_unlock(&root->orphan_lock);
		return;
	}

	block_rsv = root->orphan_block_rsv;
	root->orphan_block_rsv = NULL;
	spin_unlock(&root->orphan_lock);

	if (root->orphan_item_inserted &&
	    btrfs_root_refs(&root->root_item) > 0) {
		ret = btrfs_del_orphan_item(trans, root->fs_info->tree_root,
					    root->root_key.objectid);
		BUG_ON(ret);
		root->orphan_item_inserted = 0;
	}

	if (block_rsv) {
		WARN_ON(block_rsv->size > 0);
		btrfs_free_block_rsv(root, block_rsv);
	}
}