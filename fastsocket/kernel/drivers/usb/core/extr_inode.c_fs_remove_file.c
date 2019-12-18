#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_1__* d_inode; struct dentry* d_parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usbfs_positive (struct dentry*) ; 
 int /*<<< orphan*/  usbfs_rmdir (TYPE_1__*,struct dentry*) ; 
 int /*<<< orphan*/  usbfs_unlink (TYPE_1__*,struct dentry*) ; 

__attribute__((used)) static void fs_remove_file (struct dentry *dentry)
{
	struct dentry *parent = dentry->d_parent;
	
	if (!parent || !parent->d_inode)
		return;

	mutex_lock_nested(&parent->d_inode->i_mutex, I_MUTEX_PARENT);
	if (usbfs_positive(dentry)) {
		if (dentry->d_inode) {
			if (S_ISDIR(dentry->d_inode->i_mode))
				usbfs_rmdir(parent->d_inode, dentry);
			else
				usbfs_unlink(parent->d_inode, dentry);
		dput(dentry);
		}
	}
	mutex_unlock(&parent->d_inode->i_mutex);
}