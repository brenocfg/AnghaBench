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
struct inode {int dummy; } ;
struct ecryptfs_inode_info {int /*<<< orphan*/  lower_file_mutex; TYPE_1__* lower_file; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mm_segment_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  f_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ecryptfs_inode_info* ecryptfs_inode_to_private (struct inode*) ; 
 int /*<<< orphan*/  get_ds () ; 
 int /*<<< orphan*/  get_fs () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int vfs_read (TYPE_1__*,char*,size_t,int /*<<< orphan*/ *) ; 

int ecryptfs_read_lower(char *data, loff_t offset, size_t size,
			struct inode *ecryptfs_inode)
{
	struct ecryptfs_inode_info *inode_info =
		ecryptfs_inode_to_private(ecryptfs_inode);
	mm_segment_t fs_save;
	ssize_t rc;

	mutex_lock(&inode_info->lower_file_mutex);
	BUG_ON(!inode_info->lower_file);
	inode_info->lower_file->f_pos = offset;
	fs_save = get_fs();
	set_fs(get_ds());
	rc = vfs_read(inode_info->lower_file, data, size,
		      &inode_info->lower_file->f_pos);
	set_fs(fs_save);
	mutex_unlock(&inode_info->lower_file_mutex);
	return rc;
}