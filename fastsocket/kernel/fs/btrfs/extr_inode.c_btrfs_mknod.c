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
typedef  int /*<<< orphan*/  u64 ;
struct inode {unsigned long blocks_used; int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_op; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct btrfs_trans_handle {unsigned long blocks_used; int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_op; } ;
struct btrfs_root {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int btrfs_add_nondir (struct inode*,struct inode*,struct dentry*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_root*,unsigned long) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct inode*,struct btrfs_root*) ; 
 int btrfs_find_free_ino (struct btrfs_root*,int /*<<< orphan*/ *) ; 
 int btrfs_init_inode_security (struct inode*,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_ino (struct inode*) ; 
 struct inode* btrfs_new_inode (struct inode*,struct btrfs_root*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_special_inode_operations ; 
 struct inode* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_update_inode (struct inode*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  new_valid_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_mknod(struct inode *dir, struct dentry *dentry,
			int mode, dev_t rdev)
{
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	struct inode *inode = NULL;
	int err;
	int drop_inode = 0;
	u64 objectid;
	unsigned long nr = 0;
	u64 index = 0;

	if (!new_valid_dev(rdev))
		return -EINVAL;

	/*
	 * 2 for inode item and ref
	 * 2 for dir items
	 * 1 for xattr if selinux is on
	 */
	trans = btrfs_start_transaction(root, 5);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	err = btrfs_find_free_ino(root, &objectid);
	if (err)
		goto out_unlock;

	inode = btrfs_new_inode(trans, root, dir, dentry->d_name.name,
				dentry->d_name.len, btrfs_ino(dir), objectid,
				mode, &index);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_unlock;
	}

	err = btrfs_init_inode_security(trans, inode, dir);
	if (err) {
		drop_inode = 1;
		goto out_unlock;
	}

	/*
	* If the active LSM wants to access the inode during
	* d_instantiate it needs these. Smack checks to see
	* if the filesystem supports xattrs by looking at the
	* ops vector.
	*/

	inode->i_op = &btrfs_special_inode_operations;
	err = btrfs_add_nondir(trans, dir, dentry, inode, 0, index);
	if (err)
		drop_inode = 1;
	else {
		init_special_inode(inode, inode->i_mode, rdev);
		btrfs_update_inode(trans, root, inode);
		d_instantiate(dentry, inode);
	}
out_unlock:
	nr = trans->blocks_used;
	btrfs_end_transaction(trans, root);
	btrfs_btree_balance_dirty(root, nr);
	if (drop_inode) {
		inode_dec_link_count(inode);
		iput(inode);
	}
	return err;
}