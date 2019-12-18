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
struct dentry {struct dentry* d_parent; int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  fsstack_copy_attr_all (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rename (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  unlock_rename (struct dentry*,struct dentry*) ; 
 int vfs_rename (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,struct dentry*) ; 

__attribute__((used)) static int
ecryptfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		struct inode *new_dir, struct dentry *new_dentry)
{
	int rc;
	struct dentry *lower_old_dentry;
	struct dentry *lower_new_dentry;
	struct dentry *lower_old_dir_dentry;
	struct dentry *lower_new_dir_dentry;

	lower_old_dentry = ecryptfs_dentry_to_lower(old_dentry);
	lower_new_dentry = ecryptfs_dentry_to_lower(new_dentry);
	dget(lower_old_dentry);
	dget(lower_new_dentry);
	lower_old_dir_dentry = dget_parent(lower_old_dentry);
	lower_new_dir_dentry = dget_parent(lower_new_dentry);
	lock_rename(lower_old_dir_dentry, lower_new_dir_dentry);
	rc = vfs_rename(lower_old_dir_dentry->d_inode, lower_old_dentry,
			lower_new_dir_dentry->d_inode, lower_new_dentry);
	if (rc)
		goto out_lock;
	fsstack_copy_attr_all(new_dir, lower_new_dir_dentry->d_inode, NULL);
	if (new_dir != old_dir)
		fsstack_copy_attr_all(old_dir, lower_old_dir_dentry->d_inode, NULL);
out_lock:
	unlock_rename(lower_old_dir_dentry, lower_new_dir_dentry);
	dput(lower_new_dentry->d_parent);
	dput(lower_old_dentry->d_parent);
	dput(lower_new_dentry);
	dput(lower_old_dentry);
	return rc;
}