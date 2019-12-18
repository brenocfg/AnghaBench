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
struct inode {TYPE_1__* i_op; int /*<<< orphan*/  i_mutex; } ;
struct dentry {TYPE_2__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_flags; } ;
struct TYPE_3__ {int (* rmdir ) (struct inode*,struct dentry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  dentry_unhash (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

__attribute__((used)) static int xattr_rmdir(struct inode *dir, struct dentry *dentry)
{
	int error;
	BUG_ON(!mutex_is_locked(&dir->i_mutex));
	vfs_dq_init(dir);

	mutex_lock_nested(&dentry->d_inode->i_mutex, I_MUTEX_CHILD);
	dentry_unhash(dentry);
	error = dir->i_op->rmdir(dir, dentry);
	if (!error)
		dentry->d_inode->i_flags |= S_DEAD;
	mutex_unlock(&dentry->d_inode->i_mutex);
	if (!error)
		d_delete(dentry);
	dput(dentry);

	return error;
}