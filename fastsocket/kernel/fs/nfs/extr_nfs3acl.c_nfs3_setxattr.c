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
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int ACL_TYPE_DEFAULT ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_ACCESS ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_DEFAULT ; 
 int PTR_ERR (struct posix_acl*) ; 
 int nfs3_proc_setacl (struct inode*,int,struct posix_acl*) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int nfs3_setxattr(struct dentry *dentry, const char *name,
	     const void *value, size_t size, int flags)
{
	struct inode *inode = dentry->d_inode;
	struct posix_acl *acl;
	int type, error;

	if (strcmp(name, POSIX_ACL_XATTR_ACCESS) == 0)
		type = ACL_TYPE_ACCESS;
	else if (strcmp(name, POSIX_ACL_XATTR_DEFAULT) == 0)
		type = ACL_TYPE_DEFAULT;
	else
		return -EOPNOTSUPP;

	acl = posix_acl_from_xattr(value, size);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	error = nfs3_proc_setacl(inode, type, acl);
	posix_acl_release(acl);

	return error;
}