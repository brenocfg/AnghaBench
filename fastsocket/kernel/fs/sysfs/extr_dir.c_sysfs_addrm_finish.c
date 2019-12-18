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
struct TYPE_2__ {struct sysfs_dirent* removed_list; } ;
struct sysfs_dirent {TYPE_1__ u; } ;
struct sysfs_addrm_cxt {struct sysfs_dirent* removed; scalar_t__ cnt; struct inode* parent_inode; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_deactivate (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_drop_dentry (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_mutex ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  unmap_bin_file (struct sysfs_dirent*) ; 

void sysfs_addrm_finish(struct sysfs_addrm_cxt *acxt)
{
	/* release resources acquired by sysfs_addrm_start() */
	mutex_unlock(&sysfs_mutex);
	if (acxt->parent_inode) {
		struct inode *inode = acxt->parent_inode;

		/* if added/removed, update timestamps on the parent */
		if (acxt->cnt)
			inode->i_ctime = inode->i_mtime = CURRENT_TIME;

		mutex_unlock(&inode->i_mutex);
		iput(inode);
	}

	/* kill removed sysfs_dirents */
	while (acxt->removed) {
		struct sysfs_dirent *sd = acxt->removed;

		acxt->removed = sd->u.removed_list;

		sysfs_drop_dentry(sd);
		sysfs_deactivate(sd);
		unmap_bin_file(sd);
		sysfs_put(sd);
	}
}