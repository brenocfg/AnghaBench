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
struct inode {unsigned long blocks_used; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct btrfs_trans_handle {unsigned long blocks_used; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct btrfs_root {int dummy; } ;
struct TYPE_4__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int btrfs_add_link (struct inode*,struct inode*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_root*,unsigned long) ; 
 int /*<<< orphan*/  btrfs_dir_file_operations ; 
 int /*<<< orphan*/  btrfs_dir_inode_operations ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct inode*,struct btrfs_root*) ; 
 int btrfs_find_free_ino (struct btrfs_root*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int btrfs_init_inode_security (struct inode*,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_ino (struct inode*) ; 
 struct inode* btrfs_new_inode (struct inode*,struct btrfs_root*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct inode* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_update_inode (struct inode*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static int btrfs_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	struct inode *inode = NULL;
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	int err = 0;
	int drop_on_err = 0;
	u64 objectid = 0;
	u64 index = 0;
	unsigned long nr = 1;

	/*
	 * 2 items for inode and ref
	 * 2 items for dir items
	 * 1 for xattr if selinux is on
	 */
	trans = btrfs_start_transaction(root, 5);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	err = btrfs_find_free_ino(root, &objectid);
	if (err)
		goto out_fail;

	inode = btrfs_new_inode(trans, root, dir, dentry->d_name.name,
				dentry->d_name.len, btrfs_ino(dir), objectid,
				S_IFDIR | mode, &index);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_fail;
	}

	drop_on_err = 1;

	err = btrfs_init_inode_security(trans, inode, dir);
	if (err)
		goto out_fail;

	inode->i_op = &btrfs_dir_inode_operations;
	inode->i_fop = &btrfs_dir_file_operations;

	btrfs_i_size_write(inode, 0);
	err = btrfs_update_inode(trans, root, inode);
	if (err)
		goto out_fail;

	err = btrfs_add_link(trans, dir, inode, dentry->d_name.name,
			     dentry->d_name.len, 0, index);
	if (err)
		goto out_fail;

	d_instantiate(dentry, inode);
	drop_on_err = 0;

out_fail:
	nr = trans->blocks_used;
	btrfs_end_transaction(trans, root);
	if (drop_on_err)
		iput(inode);
	btrfs_btree_balance_dirty(root, nr);
	return err;
}