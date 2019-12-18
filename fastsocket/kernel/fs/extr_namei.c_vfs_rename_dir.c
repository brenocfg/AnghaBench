#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_3__* i_sb; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_flags; TYPE_1__* i_op; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_6__ {TYPE_2__* s_type; } ;
struct TYPE_5__ {int fs_flags; } ;
struct TYPE_4__ {int (* rename ) (struct inode*,struct dentry*,struct inode*,struct dentry*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int FS_RENAME_DOES_D_MOVE ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  S_DEAD ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dentry_unhash (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int security_inode_rename (struct inode*,struct dentry*,struct inode*,struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*,struct inode*,struct dentry*) ; 

__attribute__((used)) static int vfs_rename_dir(struct inode *old_dir, struct dentry *old_dentry,
			  struct inode *new_dir, struct dentry *new_dentry)
{
	int error = 0;
	struct inode *target;

	/*
	 * If we are going to change the parent - check write permissions,
	 * we'll need to flip '..'.
	 */
	if (new_dir != old_dir) {
		error = inode_permission(old_dentry->d_inode, MAY_WRITE);
		if (error)
			return error;
	}

	error = security_inode_rename(old_dir, old_dentry, new_dir, new_dentry);
	if (error)
		return error;

	target = new_dentry->d_inode;
	if (target) {
		mutex_lock(&target->i_mutex);
		dentry_unhash(new_dentry);
	}
	if (d_mountpoint(old_dentry)||d_mountpoint(new_dentry))
		error = -EBUSY;
	else 
		error = old_dir->i_op->rename(old_dir, old_dentry, new_dir, new_dentry);
	if (target) {
		if (!error)
			target->i_flags |= S_DEAD;
		mutex_unlock(&target->i_mutex);
		if (d_unhashed(new_dentry))
			d_rehash(new_dentry);
		dput(new_dentry);
	}
	if (!error)
		if (!(old_dir->i_sb->s_type->fs_flags & FS_RENAME_DOES_D_MOVE))
			d_move(old_dentry,new_dentry);
	return error;
}