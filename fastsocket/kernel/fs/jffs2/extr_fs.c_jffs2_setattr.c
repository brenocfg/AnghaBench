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
struct iattr {int ia_valid; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int ATTR_MODE ; 
 int inode_change_ok (int /*<<< orphan*/ ,struct iattr*) ; 
 int jffs2_acl_chmod (int /*<<< orphan*/ ) ; 
 int jffs2_do_setattr (int /*<<< orphan*/ ,struct iattr*) ; 

int jffs2_setattr(struct dentry *dentry, struct iattr *iattr)
{
	int rc;

	rc = inode_change_ok(dentry->d_inode, iattr);
	if (rc)
		return rc;

	rc = jffs2_do_setattr(dentry->d_inode, iattr);
	if (!rc && (iattr->ia_valid & ATTR_MODE))
		rc = jffs2_acl_chmod(dentry->d_inode);

	return rc;
}