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
struct inode {scalar_t__ i_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; struct inode* d_inode; } ;
struct btrfs_trans_handle {unsigned long blocks_used; } ;
struct btrfs_root {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectid; } ;
struct TYPE_6__ {TYPE_1__ location; struct btrfs_root* root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_EMPTY_DIR_SIZE ; 
 scalar_t__ BTRFS_EMPTY_SUBVOL_DIR_OBJECTID ; 
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int ENOTEMPTY ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  __unlink_end_trans (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 struct btrfs_trans_handle* __unlink_start_trans (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_root*,unsigned long) ; 
 int /*<<< orphan*/  btrfs_i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_ino (struct inode*) ; 
 int btrfs_orphan_add (struct btrfs_trans_handle*,struct inode*) ; 
 int btrfs_unlink_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_unlink_subvol (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int btrfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	int err = 0;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	struct btrfs_trans_handle *trans;
	unsigned long nr = 0;

	if (inode->i_size > BTRFS_EMPTY_DIR_SIZE ||
	    btrfs_ino(inode) == BTRFS_FIRST_FREE_OBJECTID)
		return -ENOTEMPTY;

	trans = __unlink_start_trans(dir, dentry);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	if (unlikely(btrfs_ino(inode) == BTRFS_EMPTY_SUBVOL_DIR_OBJECTID)) {
		err = btrfs_unlink_subvol(trans, root, dir,
					  BTRFS_I(inode)->location.objectid,
					  dentry->d_name.name,
					  dentry->d_name.len);
		goto out;
	}

	err = btrfs_orphan_add(trans, inode);
	if (err)
		goto out;

	/* now the directory is empty */
	err = btrfs_unlink_inode(trans, root, dir, dentry->d_inode,
				 dentry->d_name.name, dentry->d_name.len);
	if (!err)
		btrfs_i_size_write(inode, 0);
out:
	nr = trans->blocks_used;
	__unlink_end_trans(trans, root);
	btrfs_btree_balance_dirty(root, nr);

	return err;
}