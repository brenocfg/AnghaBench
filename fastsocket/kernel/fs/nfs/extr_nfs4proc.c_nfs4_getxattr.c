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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  XATTR_NAME_NFSV4_ACL ; 
 int /*<<< orphan*/  nfs4_proc_get_acl (struct inode*,void*,size_t) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

ssize_t nfs4_getxattr(struct dentry *dentry, const char *key, void *buf,
		size_t buflen)
{
	struct inode *inode = dentry->d_inode;

	if (strcmp(key, XATTR_NAME_NFSV4_ACL) != 0)
		return -EOPNOTSUPP;

	return nfs4_proc_get_acl(inode, buf, buflen);
}