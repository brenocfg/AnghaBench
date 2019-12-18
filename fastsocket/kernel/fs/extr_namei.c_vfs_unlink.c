#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_op; } ;
struct dentry {int d_flags; TYPE_2__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_3__ {int (* unlink ) (struct inode*,struct dentry*) ;} ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_link_count (TYPE_2__*) ; 
 int may_delete (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int security_inode_unlink (struct inode*,struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

int vfs_unlink(struct inode *dir, struct dentry *dentry)
{
	int error = may_delete(dir, dentry, 0);

	if (error)
		return error;

	if (!dir->i_op->unlink)
		return -EPERM;

	vfs_dq_init(dir);

	mutex_lock(&dentry->d_inode->i_mutex);
	if (d_mountpoint(dentry))
		error = -EBUSY;
	else {
		error = security_inode_unlink(dir, dentry);
		if (!error)
			error = dir->i_op->unlink(dir, dentry);
	}
	mutex_unlock(&dentry->d_inode->i_mutex);

	/* We don't d_delete() NFS sillyrenamed files--they still exist. */
	if (!error && !(dentry->d_flags & DCACHE_NFSFS_RENAMED)) {
		fsnotify_link_count(dentry->d_inode);
		d_delete(dentry);
	}

	return error;
}