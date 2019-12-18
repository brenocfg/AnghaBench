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
struct sysfs_dirent {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_fsdata; int /*<<< orphan*/ * d_op; TYPE_1__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_4__ {struct sysfs_dirent* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_dentry_ops ; 
 struct sysfs_dirent* sysfs_find_dirent (struct sysfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_get (struct sysfs_dirent*) ; 
 struct inode* sysfs_get_inode (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_mutex ; 

__attribute__((used)) static struct dentry * sysfs_lookup(struct inode *dir, struct dentry *dentry,
				struct nameidata *nd)
{
	struct dentry *ret = NULL;
	struct sysfs_dirent *parent_sd = dentry->d_parent->d_fsdata;
	struct sysfs_dirent *sd;
	struct inode *inode;

	mutex_lock(&sysfs_mutex);

	sd = sysfs_find_dirent(parent_sd, dentry->d_name.name);

	/* no such entry */
	if (!sd) {
		ret = ERR_PTR(-ENOENT);
		goto out_unlock;
	}

	/* attach dentry and inode */
	inode = sysfs_get_inode(sd);
	if (!inode) {
		ret = ERR_PTR(-ENOMEM);
		goto out_unlock;
	}

	/* instantiate and hash dentry */
	dentry->d_op = &sysfs_dentry_ops;
	dentry->d_fsdata = sysfs_get(sd);
	d_instantiate(dentry, inode);
	d_rehash(dentry);

 out_unlock:
	mutex_unlock(&sysfs_mutex);
	return ret;
}