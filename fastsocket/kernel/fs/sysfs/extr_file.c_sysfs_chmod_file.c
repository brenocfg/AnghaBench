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
struct sysfs_dirent {int s_mode; } ;
struct kobject {int /*<<< orphan*/  sd; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_sb; } ;
struct iattr {int ia_mode; int ia_valid; int /*<<< orphan*/  ia_ctime; } ;
struct dentry {struct inode* d_inode; } ;
struct attribute {int /*<<< orphan*/  name; } ;
typedef  int mode_t ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_MODE ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IALLUGO ; 
 int /*<<< orphan*/  current_fs_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_change (struct dentry*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dentry* sysfs_get_dentry (struct sysfs_dirent*) ; 
 struct sysfs_dirent* sysfs_get_dirent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_mutex ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_rename_mutex ; 
 int sysfs_setattr (struct dentry*,struct iattr*) ; 

int sysfs_chmod_file(struct kobject *kobj, struct attribute *attr, mode_t mode)
{
	struct sysfs_dirent *victim_sd = NULL;
	struct dentry *victim = NULL;
	struct inode * inode;
	struct iattr newattrs;
	int rc;

	rc = -ENOENT;
	victim_sd = sysfs_get_dirent(kobj->sd, attr->name);
	if (!victim_sd)
		goto out;

	mutex_lock(&sysfs_rename_mutex);
	victim = sysfs_get_dentry(victim_sd);
	mutex_unlock(&sysfs_rename_mutex);
	if (IS_ERR(victim)) {
		rc = PTR_ERR(victim);
		victim = NULL;
		goto out;
	}

	inode = victim->d_inode;

	mutex_lock(&inode->i_mutex);

	newattrs.ia_mode = (mode & S_IALLUGO) | (inode->i_mode & ~S_IALLUGO);
	newattrs.ia_valid = ATTR_MODE | ATTR_CTIME;
	newattrs.ia_ctime = current_fs_time(inode->i_sb);
	rc = sysfs_setattr(victim, &newattrs);

	if (rc == 0) {
		fsnotify_change(victim, newattrs.ia_valid);
		mutex_lock(&sysfs_mutex);
		victim_sd->s_mode = newattrs.ia_mode;
		mutex_unlock(&sysfs_mutex);
	}

	mutex_unlock(&inode->i_mutex);
 out:
	dput(victim);
	sysfs_put(victim_sd);
	return rc;
}