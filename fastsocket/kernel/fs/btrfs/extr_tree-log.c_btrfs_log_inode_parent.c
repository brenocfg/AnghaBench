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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; int /*<<< orphan*/  i_mode; } ;
struct dentry {struct inode* d_inode; } ;
struct btrfs_trans_handle {scalar_t__ transid; } ;
struct btrfs_root {TYPE_1__* fs_info; int /*<<< orphan*/  root_item; } ;
struct TYPE_4__ {scalar_t__ generation; scalar_t__ last_unlink_trans; struct btrfs_root* root; } ;
struct TYPE_3__ {scalar_t__ last_trans_committed; scalar_t__ last_trans_log_full_commit; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int BTRFS_NO_LOG_SYNC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int LOG_INODE_ALL ; 
 int LOG_INODE_EXISTS ; 
 int /*<<< orphan*/  NOTREELOG ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_log_trans (struct btrfs_root*) ; 
 scalar_t__ btrfs_inode_in_log (struct inode*,scalar_t__) ; 
 int btrfs_log_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,int) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int check_parent_dirs_for_sync (struct btrfs_trans_handle*,struct inode*,struct dentry*,struct super_block*,scalar_t__) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int start_log_trans (struct btrfs_trans_handle*,struct btrfs_root*) ; 

int btrfs_log_inode_parent(struct btrfs_trans_handle *trans,
		    struct btrfs_root *root, struct inode *inode,
		    struct dentry *parent, int exists_only)
{
	int inode_only = exists_only ? LOG_INODE_EXISTS : LOG_INODE_ALL;
	struct super_block *sb;
	struct dentry *old_parent = NULL;
	int ret = 0;
	u64 last_committed = root->fs_info->last_trans_committed;

	sb = inode->i_sb;

	if (btrfs_test_opt(root, NOTREELOG)) {
		ret = 1;
		goto end_no_trans;
	}

	if (root->fs_info->last_trans_log_full_commit >
	    root->fs_info->last_trans_committed) {
		ret = 1;
		goto end_no_trans;
	}

	if (root != BTRFS_I(inode)->root ||
	    btrfs_root_refs(&root->root_item) == 0) {
		ret = 1;
		goto end_no_trans;
	}

	ret = check_parent_dirs_for_sync(trans, inode, parent,
					 sb, last_committed);
	if (ret)
		goto end_no_trans;

	if (btrfs_inode_in_log(inode, trans->transid)) {
		ret = BTRFS_NO_LOG_SYNC;
		goto end_no_trans;
	}

	ret = start_log_trans(trans, root);
	if (ret)
		goto end_trans;

	ret = btrfs_log_inode(trans, root, inode, inode_only);
	if (ret)
		goto end_trans;

	/*
	 * for regular files, if its inode is already on disk, we don't
	 * have to worry about the parents at all.  This is because
	 * we can use the last_unlink_trans field to record renames
	 * and other fun in this file.
	 */
	if (S_ISREG(inode->i_mode) &&
	    BTRFS_I(inode)->generation <= last_committed &&
	    BTRFS_I(inode)->last_unlink_trans <= last_committed) {
		ret = 0;
		goto end_trans;
	}

	inode_only = LOG_INODE_EXISTS;
	while (1) {
		if (!parent || !parent->d_inode || sb != parent->d_inode->i_sb)
			break;

		inode = parent->d_inode;
		if (root != BTRFS_I(inode)->root)
			break;

		if (BTRFS_I(inode)->generation >
		    root->fs_info->last_trans_committed) {
			ret = btrfs_log_inode(trans, root, inode, inode_only);
			if (ret)
				goto end_trans;
		}
		if (IS_ROOT(parent))
			break;

		parent = dget_parent(parent);
		dput(old_parent);
		old_parent = parent;
	}
	ret = 0;
end_trans:
	dput(old_parent);
	if (ret < 0) {
		BUG_ON(ret != -ENOSPC);
		root->fs_info->last_trans_log_full_commit = trans->transid;
		ret = 1;
	}
	btrfs_end_log_trans(root);
end_no_trans:
	return ret;
}