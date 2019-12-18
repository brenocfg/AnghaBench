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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct iattr {int ia_valid; } ;
struct dentry {struct inode* d_inode; } ;
struct btrfs_root {int dummy; } ;
struct TYPE_2__ {struct btrfs_root* root; } ;

/* Variables and functions */
 int ATTR_MODE ; 
 int ATTR_SIZE ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int EROFS ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int btrfs_acl_chmod (struct inode*) ; 
 scalar_t__ btrfs_root_readonly (struct btrfs_root*) ; 
 int btrfs_setsize (struct inode*,struct iattr*) ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int inode_setattr (struct inode*,struct iattr*) ; 

__attribute__((used)) static int btrfs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = dentry->d_inode;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int err;

	if (btrfs_root_readonly(root))
		return -EROFS;

	err = inode_change_ok(inode, attr);
	if (err)
		return err;

	if (S_ISREG(inode->i_mode) && (attr->ia_valid & ATTR_SIZE)) {
		err = btrfs_setsize(inode, attr);
		if (err)
			return err;
	}
	attr->ia_valid &= ~ATTR_SIZE;

	if (attr->ia_valid) {
		inode_inc_iversion(inode);
		err = inode_setattr(inode, attr);
	}

	if (!err && ((attr->ia_valid & ATTR_MODE)))
		err = btrfs_acl_chmod(inode);
	return err;
}