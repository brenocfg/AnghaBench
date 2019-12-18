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
struct vfsmount {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {struct dentry* dentry; struct vfsmount* mnt; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mnt_drop_write (struct vfsmount*) ; 
 scalar_t__ file_check_writeable (struct file*) ; 
 int /*<<< orphan*/  file_release_write (struct file*) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 
 scalar_t__ special_file (int /*<<< orphan*/ ) ; 

void drop_file_write_access(struct file *file)
{
	struct vfsmount *mnt = file->f_path.mnt;
	struct dentry *dentry = file->f_path.dentry;
	struct inode *inode = dentry->d_inode;

	put_write_access(inode);

	if (special_file(inode->i_mode))
		return;
	if (file_check_writeable(file) != 0)
		return;
	__mnt_drop_write(mnt);
	file_release_write(file);
}