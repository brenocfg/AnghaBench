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
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mount ; 
 int /*<<< orphan*/  mount_count ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ positive (struct dentry*) ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_rmdir (TYPE_1__*,struct dentry*) ; 
 int /*<<< orphan*/  simple_unlink (TYPE_1__*,struct dentry*) ; 

void securityfs_remove(struct dentry *dentry)
{
	struct dentry *parent;

	if (!dentry || IS_ERR(dentry))
		return;

	parent = dentry->d_parent;
	if (!parent || !parent->d_inode)
		return;

	mutex_lock(&parent->d_inode->i_mutex);
	if (positive(dentry)) {
		if (dentry->d_inode) {
			if (S_ISDIR(dentry->d_inode->i_mode))
				simple_rmdir(parent->d_inode, dentry);
			else
				simple_unlink(parent->d_inode, dentry);
			dput(dentry);
		}
	}
	mutex_unlock(&parent->d_inode->i_mutex);
	simple_release_fs(&mount, &mount_count);
}