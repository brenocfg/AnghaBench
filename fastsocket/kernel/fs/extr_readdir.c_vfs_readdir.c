#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {TYPE_3__* f_op; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_6__ {int (* readdir ) (struct file*,void*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  IS_DEADDIR (struct inode*) ; 
 int /*<<< orphan*/  MAY_READ ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int security_file_permission (struct file*,int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,void*,int /*<<< orphan*/ ) ; 

int vfs_readdir(struct file *file, filldir_t filler, void *buf)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	int res = -ENOTDIR;
	if (!file->f_op || !file->f_op->readdir)
		goto out;

	res = security_file_permission(file, MAY_READ);
	if (res)
		goto out;

	res = mutex_lock_killable(&inode->i_mutex);
	if (res)
		goto out;

	res = -ENOENT;
	if (!IS_DEADDIR(inode)) {
		res = file->f_op->readdir(file, buf, filler);
		file_accessed(file);
	}
	mutex_unlock(&inode->i_mutex);
out:
	return res;
}