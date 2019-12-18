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
struct dentry {TYPE_1__* d_inode; struct configfs_dirent* d_fsdata; } ;
struct configfs_dirent {int /*<<< orphan*/  s_type; } ;
struct config_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGFS_USET_DIR ; 
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  configfs_adjust_dir_dirent_depth_after_populate (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_adjust_dir_dirent_depth_before_populate (struct configfs_dirent*) ; 
 int configfs_attach_item (struct config_item*,struct config_item*,struct dentry*) ; 
 int /*<<< orphan*/  configfs_detach_item (struct config_item*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int populate_groups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 

__attribute__((used)) static int configfs_attach_group(struct config_item *parent_item,
				 struct config_item *item,
				 struct dentry *dentry)
{
	int ret;
	struct configfs_dirent *sd;

	ret = configfs_attach_item(parent_item, item, dentry);
	if (!ret) {
		sd = dentry->d_fsdata;
		sd->s_type |= CONFIGFS_USET_DIR;

		/*
		 * FYI, we're faking mkdir in populate_groups()
		 * We must lock the group's inode to avoid races with the VFS
		 * which can already hit the inode and try to add/remove entries
		 * under it.
		 *
		 * We must also lock the inode to remove it safely in case of
		 * error, as rmdir() would.
		 */
		mutex_lock_nested(&dentry->d_inode->i_mutex, I_MUTEX_CHILD);
		configfs_adjust_dir_dirent_depth_before_populate(sd);
		ret = populate_groups(to_config_group(item));
		if (ret) {
			configfs_detach_item(item);
			dentry->d_inode->i_flags |= S_DEAD;
		}
		configfs_adjust_dir_dirent_depth_after_populate(sd);
		mutex_unlock(&dentry->d_inode->i_mutex);
		if (ret)
			d_delete(dentry);
	}

	return ret;
}