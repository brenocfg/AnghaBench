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
struct dentry {TYPE_1__* d_inode; } ;
struct config_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_DEAD ; 
 int configfs_create_dir (struct config_item*,struct dentry*) ; 
 int /*<<< orphan*/  configfs_remove_dir (struct config_item*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int populate_attrs (struct config_item*) ; 

__attribute__((used)) static int configfs_attach_item(struct config_item *parent_item,
				struct config_item *item,
				struct dentry *dentry)
{
	int ret;

	ret = configfs_create_dir(item, dentry);
	if (!ret) {
		ret = populate_attrs(item);
		if (ret) {
			/*
			 * We are going to remove an inode and its dentry but
			 * the VFS may already have hit and used them. Thus,
			 * we must lock them as rmdir() would.
			 */
			mutex_lock(&dentry->d_inode->i_mutex);
			configfs_remove_dir(item);
			dentry->d_inode->i_flags |= S_DEAD;
			mutex_unlock(&dentry->d_inode->i_mutex);
			d_delete(dentry);
		}
	}

	return ret;
}