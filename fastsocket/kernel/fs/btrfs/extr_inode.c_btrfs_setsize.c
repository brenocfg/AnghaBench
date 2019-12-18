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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; } ;
struct iattr {scalar_t__ ia_size; int ia_valid; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_ORDERED_DATA_CLOSE ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int btrfs_cont_expand (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_ordered_update_i_size (struct inode*,scalar_t__,int /*<<< orphan*/ *) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_truncate (struct inode*) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  current_fs_time (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 

__attribute__((used)) static int btrfs_setsize(struct inode *inode, struct iattr *attr)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_trans_handle *trans;
	loff_t oldsize = i_size_read(inode);
	loff_t newsize = attr->ia_size;
	int mask = attr->ia_valid;
	int ret;

	if (newsize == oldsize)
		return 0;

	/*
	 * The regular truncate() case without ATTR_CTIME and ATTR_MTIME is a
	 * special case where we need to update the times despite not having
	 * these flags set.  For all other operations the VFS set these flags
	 * explicitly if it wants a timestamp update.
	 */
	if (newsize != oldsize && (!(mask & (ATTR_CTIME | ATTR_MTIME))))
		inode->i_ctime = inode->i_mtime = current_fs_time(inode->i_sb);

	if (newsize > oldsize) {
		truncate_pagecache(inode, oldsize, newsize);
		ret = btrfs_cont_expand(inode, oldsize, newsize);
		if (ret)
			return ret;

		trans = btrfs_start_transaction(root, 1);
		if (IS_ERR(trans))
			return PTR_ERR(trans);

		i_size_write(inode, newsize);
		btrfs_ordered_update_i_size(inode, i_size_read(inode), NULL);
		ret = btrfs_update_inode(trans, root, inode);
		btrfs_end_transaction(trans, root);
	} else {

		/*
		 * We're truncating a file that used to have good data down to
		 * zero. Make sure it gets into the ordered flush list so that
		 * any new writes get down to disk quickly.
		 */
		if (newsize == 0)
			set_bit(BTRFS_INODE_ORDERED_DATA_CLOSE,
				&BTRFS_I(inode)->runtime_flags);

		/* we don't support swapfiles, so vmtruncate shouldn't fail */
		truncate_setsize(inode, newsize);
		ret = btrfs_truncate(inode);
	}

	return ret;
}