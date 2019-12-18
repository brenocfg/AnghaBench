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
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;
struct iattr {int /*<<< orphan*/  ia_mode; } ;
struct gfs2_inode {struct inode i_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 struct posix_acl* gfs2_acl_get (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int gfs2_setattr_simple (struct inode*,struct iattr*) ; 
 int gfs2_xattr_acl_chmod (struct gfs2_inode*,struct iattr*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int posix_acl_chmod_masq (struct posix_acl*,int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_clone (struct posix_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 unsigned int posix_acl_to_xattr (struct posix_acl*,char*,unsigned int) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int /*<<< orphan*/ ,struct posix_acl*) ; 

int gfs2_acl_chmod(struct gfs2_inode *ip, struct iattr *attr)
{
	struct inode *inode = &ip->i_inode;
	struct posix_acl *acl, *clone;
	char *data;
	unsigned int len;
	int error;

	acl = gfs2_acl_get(ip, ACL_TYPE_ACCESS);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (!acl)
		return gfs2_setattr_simple(inode, attr);

	clone = posix_acl_clone(acl, GFP_NOFS);
	error = -ENOMEM;
	if (!clone)
		goto out;
	posix_acl_release(acl);
	acl = clone;

	error = posix_acl_chmod_masq(acl, attr->ia_mode);
	if (!error) {
		len = posix_acl_to_xattr(acl, NULL, 0);
		data = kmalloc(len, GFP_NOFS);
		error = -ENOMEM;
		if (data == NULL)
			goto out;
		posix_acl_to_xattr(acl, data, len);
		error = gfs2_xattr_acl_chmod(ip, attr, data);
		kfree(data);
		set_cached_acl(&ip->i_inode, ACL_TYPE_ACCESS, acl);
	}

out:
	posix_acl_release(acl);
	return error;
}