#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct btrfs_trans_handle {struct btrfs_block_rsv* block_rsv; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_block_rsv {scalar_t__ reserved; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct btrfs_block_rsv global_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_EXTENT_DATA_KEY ; 
 int ENOSPC ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 scalar_t__ btrfs_calc_trans_metadata_size (struct btrfs_root*,int) ; 
 scalar_t__ btrfs_calc_trunc_metadata_size (struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int btrfs_truncate_inode_items (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_truncate_free_space_cache(struct btrfs_root *root,
				    struct btrfs_trans_handle *trans,
				    struct btrfs_path *path,
				    struct inode *inode)
{
	struct btrfs_block_rsv *rsv;
	u64 needed_bytes;
	loff_t oldsize;
	int ret = 0;

	rsv = trans->block_rsv;
	trans->block_rsv = &root->fs_info->global_block_rsv;

	/* 1 for slack space, 1 for updating the inode */
	needed_bytes = btrfs_calc_trunc_metadata_size(root, 1) +
		btrfs_calc_trans_metadata_size(root, 1);

	spin_lock(&trans->block_rsv->lock);
	if (trans->block_rsv->reserved < needed_bytes) {
		spin_unlock(&trans->block_rsv->lock);
		trans->block_rsv = rsv;
		return -ENOSPC;
	}
	spin_unlock(&trans->block_rsv->lock);

	oldsize = i_size_read(inode);
	btrfs_i_size_write(inode, 0);
	truncate_pagecache(inode, oldsize, 0);

	/*
	 * We don't need an orphan item because truncating the free space cache
	 * will never be split across transactions.
	 */
	ret = btrfs_truncate_inode_items(trans, root, inode,
					 0, BTRFS_EXTENT_DATA_KEY);

	if (ret) {
		trans->block_rsv = rsv;
		btrfs_abort_transaction(trans, root, ret);
		return ret;
	}

	ret = btrfs_update_inode(trans, root, inode);
	if (ret)
		btrfs_abort_transaction(trans, root, ret);
	trans->block_rsv = rsv;

	return ret;
}