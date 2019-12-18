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
struct posix_acl {scalar_t__ a_count; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int ACL_TYPE_DEFAULT ; 
 int ENODATA ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_ACCESS ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_DEFAULT ; 
 int PTR_ERR (struct posix_acl*) ; 
 struct posix_acl* nfs3_proc_getacl (struct inode*,int) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_to_xattr (struct posix_acl*,void*,size_t) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

ssize_t nfs3_getxattr(struct dentry *dentry, const char *name,
		void *buffer, size_t size)
{
	struct inode *inode = dentry->d_inode;
	struct posix_acl *acl;
	int type, error = 0;

	if (strcmp(name, POSIX_ACL_XATTR_ACCESS) == 0)
		type = ACL_TYPE_ACCESS;
	else if (strcmp(name, POSIX_ACL_XATTR_DEFAULT) == 0)
		type = ACL_TYPE_DEFAULT;
	else
		return -EOPNOTSUPP;

	acl = nfs3_proc_getacl(inode, type);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	else if (acl) {
		if (type == ACL_TYPE_ACCESS && acl->a_count == 0)
			error = -ENODATA;
		else
			error = posix_acl_to_xattr(acl, buffer, size);
		posix_acl_release(acl);
	} else
		error = -ENODATA;

	return error;
}