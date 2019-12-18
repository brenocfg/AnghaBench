#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  transid; TYPE_1__* transaction; } ;
struct dentry {TYPE_3__* d_parent; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; TYPE_1__* transaction; } ;
struct btrfs_root {TYPE_2__* fs_info; int /*<<< orphan*/  ref_cows; } ;
struct btrfs_pending_snapshot {int readonly; int error; int /*<<< orphan*/  snap; int /*<<< orphan*/  list; struct btrfs_root* root; struct dentry* dentry; int /*<<< orphan*/  block_rsv; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  extent_root; int /*<<< orphan*/  trans_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  pending_snapshots; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int btrfs_commit_transaction (struct inode*,int /*<<< orphan*/ ) ; 
 int btrfs_commit_transaction_async (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_init_block_rsv (int /*<<< orphan*/ *) ; 
 struct inode* btrfs_lookup_dentry (int /*<<< orphan*/ ,struct dentry*) ; 
 int btrfs_orphan_cleanup (int /*<<< orphan*/ ) ; 
 int btrfs_snap_reserve_metadata (struct inode*,struct btrfs_pending_snapshot*) ; 
 struct inode* btrfs_start_transaction (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  kfree (struct btrfs_pending_snapshot*) ; 
 struct btrfs_pending_snapshot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_snapshot(struct btrfs_root *root, struct dentry *dentry,
			   char *name, int namelen, u64 *async_transid,
			   bool readonly)
{
	struct inode *inode;
	struct btrfs_pending_snapshot *pending_snapshot;
	struct btrfs_trans_handle *trans;
	int ret;

	if (!root->ref_cows)
		return -EINVAL;

	pending_snapshot = kzalloc(sizeof(*pending_snapshot), GFP_NOFS);
	if (!pending_snapshot)
		return -ENOMEM;

	btrfs_init_block_rsv(&pending_snapshot->block_rsv);
	pending_snapshot->dentry = dentry;
	pending_snapshot->root = root;
	pending_snapshot->readonly = readonly;

	trans = btrfs_start_transaction(root->fs_info->extent_root, 5);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		goto fail;
	}

	ret = btrfs_snap_reserve_metadata(trans, pending_snapshot);
	BUG_ON(ret);

	spin_lock(&root->fs_info->trans_lock);
	list_add(&pending_snapshot->list,
		 &trans->transaction->pending_snapshots);
	spin_unlock(&root->fs_info->trans_lock);
	if (async_transid) {
		*async_transid = trans->transid;
		ret = btrfs_commit_transaction_async(trans,
				     root->fs_info->extent_root, 1);
	} else {
		ret = btrfs_commit_transaction(trans,
					       root->fs_info->extent_root);
	}
	BUG_ON(ret);

	ret = pending_snapshot->error;
	if (ret)
		goto fail;

	ret = btrfs_orphan_cleanup(pending_snapshot->snap);
	if (ret)
		goto fail;

	inode = btrfs_lookup_dentry(dentry->d_parent->d_inode, dentry);
	if (IS_ERR(inode)) {
		ret = PTR_ERR(inode);
		goto fail;
	}
	BUG_ON(!inode);
	d_instantiate(dentry, inode);
	ret = 0;
fail:
	kfree(pending_snapshot);
	return ret;
}