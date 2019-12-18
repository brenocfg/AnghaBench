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
struct inode {int dummy; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {int /*<<< orphan*/  private_data; TYPE_1__ f_path; } ;
struct dentry {TYPE_2__* d_inode; struct configfs_dirent* d_fsdata; } ;
struct configfs_dirent {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ configfs_dirent_is_ready (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_new_dirent (struct configfs_dirent*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int configfs_dir_open(struct inode *inode, struct file *file)
{
	struct dentry * dentry = file->f_path.dentry;
	struct configfs_dirent * parent_sd = dentry->d_fsdata;
	int err;

	mutex_lock(&dentry->d_inode->i_mutex);
	/*
	 * Fake invisibility if dir belongs to a group/default groups hierarchy
	 * being attached
	 */
	err = -ENOENT;
	if (configfs_dirent_is_ready(parent_sd)) {
		file->private_data = configfs_new_dirent(parent_sd, NULL, 0);
		if (IS_ERR(file->private_data))
			err = PTR_ERR(file->private_data);
		else
			err = 0;
	}
	mutex_unlock(&dentry->d_inode->i_mutex);

	return err;
}