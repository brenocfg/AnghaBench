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
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAY_WRITE ; 
 int __vfs_setxattr_noperm (struct dentry*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int security_inode_setxattr (struct dentry*,char const*,void const*,size_t,int) ; 
 int xattr_permission (struct inode*,char const*,int /*<<< orphan*/ ) ; 

int
vfs_setxattr(struct dentry *dentry, const char *name, const void *value,
		size_t size, int flags)
{
	struct inode *inode = dentry->d_inode;
	int error;

	error = xattr_permission(inode, name, MAY_WRITE);
	if (error)
		return error;

	mutex_lock(&inode->i_mutex);
	error = security_inode_setxattr(dentry, name, value, size, flags);
	if (error)
		goto out;

	error = __vfs_setxattr_noperm(dentry, name, value, size, flags);

out:
	mutex_unlock(&inode->i_mutex);
	return error;
}