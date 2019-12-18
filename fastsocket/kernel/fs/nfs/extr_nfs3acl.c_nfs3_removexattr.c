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
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int ACL_TYPE_DEFAULT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_ACCESS ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_DEFAULT ; 
 int nfs3_proc_setacl (struct inode*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int nfs3_removexattr(struct dentry *dentry, const char *name)
{
	struct inode *inode = dentry->d_inode;
	int type;

	if (strcmp(name, POSIX_ACL_XATTR_ACCESS) == 0)
		type = ACL_TYPE_ACCESS;
	else if (strcmp(name, POSIX_ACL_XATTR_DEFAULT) == 0)
		type = ACL_TYPE_DEFAULT;
	else
		return -EOPNOTSUPP;

	return nfs3_proc_setacl(inode, type, NULL);
}