#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sysfs_dirent {char* s_name; int /*<<< orphan*/  s_parent; } ;
struct kobject {struct sysfs_dirent* sd; } ;
struct dentry {TYPE_1__* d_inode; struct dentry* d_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_alloc_name (struct dentry*,char const*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ sysfs_find_dirent (int /*<<< orphan*/ ,char const*) ; 
 struct dentry* sysfs_get_dentry (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_link_sibling (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_mutex ; 
 int /*<<< orphan*/  sysfs_rename_mutex ; 
 int /*<<< orphan*/  sysfs_unlink_sibling (struct sysfs_dirent*) ; 

int sysfs_rename_dir(struct kobject * kobj, const char *new_name)
{
	struct sysfs_dirent *sd = kobj->sd;
	struct dentry *parent = NULL;
	struct dentry *old_dentry = NULL, *new_dentry = NULL;
	const char *dup_name = NULL;
	int error;

	mutex_lock(&sysfs_rename_mutex);

	error = 0;
	if (strcmp(sd->s_name, new_name) == 0)
		goto out;	/* nothing to rename */

	/* get the original dentry */
	old_dentry = sysfs_get_dentry(sd);
	if (IS_ERR(old_dentry)) {
		error = PTR_ERR(old_dentry);
		old_dentry = NULL;
		goto out;
	}

	parent = old_dentry->d_parent;

	/* lock parent and get dentry for new name */
	mutex_lock(&parent->d_inode->i_mutex);
	mutex_lock(&sysfs_mutex);

	error = -EEXIST;
	if (sysfs_find_dirent(sd->s_parent, new_name))
		goto out_unlock;

	error = -ENOMEM;
	new_dentry = d_alloc_name(parent, new_name);
	if (!new_dentry)
		goto out_unlock;

	/* rename sysfs_dirent */
	error = -ENOMEM;
	new_name = dup_name = kstrdup(new_name, GFP_KERNEL);
	if (!new_name)
		goto out_unlock;

	sysfs_unlink_sibling(sd);
	dup_name = sd->s_name;
	sd->s_name = new_name;
	sysfs_link_sibling(sd);

	/* rename */
	d_add(new_dentry, NULL);
	d_move(old_dentry, new_dentry);

	error = 0;
 out_unlock:
	mutex_unlock(&sysfs_mutex);
	mutex_unlock(&parent->d_inode->i_mutex);
	kfree(dup_name);
	dput(old_dentry);
	dput(new_dentry);
 out:
	mutex_unlock(&sysfs_rename_mutex);
	return error;
}