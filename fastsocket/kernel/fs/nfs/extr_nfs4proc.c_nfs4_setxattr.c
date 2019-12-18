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
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XATTR_NAME_NFSV4_ACL ; 
 int nfs4_proc_set_acl (struct inode*,void const*,size_t) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int nfs4_setxattr(struct dentry *dentry, const char *key, const void *buf,
		size_t buflen, int flags)
{
	struct inode *inode = dentry->d_inode;

	if (strcmp(key, XATTR_NAME_NFSV4_ACL) != 0)
		return -EOPNOTSUPP;

	return nfs4_proc_set_acl(inode, buf, buflen);
}