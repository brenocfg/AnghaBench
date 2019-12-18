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
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_flags; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOTEMPTY ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  dentry_unhash (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usbfs_empty (struct dentry*) ; 

__attribute__((used)) static int usbfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	int error = -ENOTEMPTY;
	struct inode * inode = dentry->d_inode;

	mutex_lock(&inode->i_mutex);
	dentry_unhash(dentry);
	if (usbfs_empty(dentry)) {
		drop_nlink(dentry->d_inode);
		drop_nlink(dentry->d_inode);
		dput(dentry);
		inode->i_flags |= S_DEAD;
		drop_nlink(dir);
		error = 0;
	}
	mutex_unlock(&inode->i_mutex);
	if (!error)
		d_delete(dentry);
	dput(dentry);
	return error;
}