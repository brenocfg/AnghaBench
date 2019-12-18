#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {scalar_t__ i_uid; scalar_t__ i_gid; } ;
struct iattr {int ia_valid; scalar_t__ ia_uid; scalar_t__ ia_gid; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int EDQUOT ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 
 int inode_setattr (struct inode*,struct iattr*) ; 
 int jfs_acl_chmod (struct inode*) ; 
 scalar_t__ vfs_dq_transfer (struct inode*,struct iattr*) ; 

int jfs_setattr(struct dentry *dentry, struct iattr *iattr)
{
	struct inode *inode = dentry->d_inode;
	int rc;

	rc = inode_change_ok(inode, iattr);
	if (rc)
		return rc;

	if ((iattr->ia_valid & ATTR_UID && iattr->ia_uid != inode->i_uid) ||
	    (iattr->ia_valid & ATTR_GID && iattr->ia_gid != inode->i_gid)) {
		if (vfs_dq_transfer(inode, iattr))
			return -EDQUOT;
	}

	rc = inode_setattr(inode, iattr);

	if (!rc && (iattr->ia_valid & ATTR_MODE))
		rc = jfs_acl_chmod(inode);

	return rc;
}