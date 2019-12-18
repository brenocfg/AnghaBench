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
struct sysfs_dirent {struct sysfs_dirent* s_parent; int /*<<< orphan*/  s_name; } ;
struct kobject {struct sysfs_dirent* sd; } ;
struct dentry {TYPE_1__* d_inode; struct dentry* d_parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EEXIST ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_alloc_name (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (TYPE_1__*) ; 
 int /*<<< orphan*/  inc_nlink (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_find_dirent (struct sysfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_get (struct sysfs_dirent*) ; 
 struct dentry* sysfs_get_dentry (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_link_sibling (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_mutex ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_rename_mutex ; 
 struct sysfs_dirent sysfs_root ; 
 int /*<<< orphan*/  sysfs_unlink_sibling (struct sysfs_dirent*) ; 

int sysfs_move_dir(struct kobject *kobj, struct kobject *new_parent_kobj)
{
	struct sysfs_dirent *sd = kobj->sd;
	struct sysfs_dirent *new_parent_sd;
	struct dentry *old_parent, *new_parent = NULL;
	struct dentry *old_dentry = NULL, *new_dentry = NULL;
	int error;

	mutex_lock(&sysfs_rename_mutex);
	BUG_ON(!sd->s_parent);
	new_parent_sd = (new_parent_kobj && new_parent_kobj->sd) ?
		new_parent_kobj->sd : &sysfs_root;

	error = 0;
	if (sd->s_parent == new_parent_sd)
		goto out;	/* nothing to move */

	/* get dentries */
	old_dentry = sysfs_get_dentry(sd);
	if (IS_ERR(old_dentry)) {
		error = PTR_ERR(old_dentry);
		old_dentry = NULL;
		goto out;
	}
	old_parent = old_dentry->d_parent;

	new_parent = sysfs_get_dentry(new_parent_sd);
	if (IS_ERR(new_parent)) {
		error = PTR_ERR(new_parent);
		new_parent = NULL;
		goto out;
	}

again:
	mutex_lock(&old_parent->d_inode->i_mutex);
	if (!mutex_trylock(&new_parent->d_inode->i_mutex)) {
		mutex_unlock(&old_parent->d_inode->i_mutex);
		goto again;
	}
	mutex_lock(&sysfs_mutex);

	error = -EEXIST;
	if (sysfs_find_dirent(new_parent_sd, sd->s_name))
		goto out_unlock;

	error = -ENOMEM;
	new_dentry = d_alloc_name(new_parent, sd->s_name);
	if (!new_dentry)
		goto out_unlock;

	error = 0;
	d_add(new_dentry, NULL);
	d_move(old_dentry, new_dentry);

	/* Remove from old parent's list and insert into new parent's list. */
	sysfs_unlink_sibling(sd);
	sysfs_get(new_parent_sd);
	drop_nlink(old_parent->d_inode);
	sysfs_put(sd->s_parent);
	sd->s_parent = new_parent_sd;
	inc_nlink(new_parent->d_inode);
	sysfs_link_sibling(sd);

 out_unlock:
	mutex_unlock(&sysfs_mutex);
	mutex_unlock(&new_parent->d_inode->i_mutex);
	mutex_unlock(&old_parent->d_inode->i_mutex);
 out:
	dput(new_parent);
	dput(old_dentry);
	dput(new_dentry);
	mutex_unlock(&sysfs_rename_mutex);
	return error;
}