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
struct inode {TYPE_2__* i_op; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_4__ {int (* rmdir ) (struct inode*,struct dentry*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  dentry_unhash (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int may_delete (struct inode*,struct dentry*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int security_inode_rmdir (struct inode*,struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

int vfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	int error = may_delete(dir, dentry, 1);

	if (error)
		return error;

	if (!dir->i_op->rmdir)
		return -EPERM;

	vfs_dq_init(dir);

	mutex_lock(&dentry->d_inode->i_mutex);
	dentry_unhash(dentry);
	if (d_mountpoint(dentry))
		error = -EBUSY;
	else {
		error = security_inode_rmdir(dir, dentry);
		if (!error) {
			error = dir->i_op->rmdir(dir, dentry);
			if (!error)
				dentry->d_inode->i_flags |= S_DEAD;
		}
	}
	mutex_unlock(&dentry->d_inode->i_mutex);
	if (!error) {
		d_delete(dentry);
	}
	dput(dentry);

	return error;
}