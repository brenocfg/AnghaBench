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
struct vfsmount {int dummy; } ;
struct inode {int /*<<< orphan*/ * i_cdev; int /*<<< orphan*/  i_mode; } ;
struct TYPE_5__ {struct vfsmount* mnt; struct dentry* dentry; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct file {int f_flags; int f_mode; TYPE_2__ f_path; TYPE_1__ f_owner; TYPE_3__* f_op; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* release ) (struct inode*,struct file*) ;int /*<<< orphan*/  (* fasync ) (int,struct file*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int FASYNC ; 
 int FMODE_WRITE ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  drop_file_write_access (struct file*) ; 
 int /*<<< orphan*/  eventpoll_release (struct file*) ; 
 int /*<<< orphan*/  file_free (struct file*) ; 
 int /*<<< orphan*/  file_kill (struct file*) ; 
 int /*<<< orphan*/  fops_put (TYPE_3__*) ; 
 int /*<<< orphan*/  fsnotify_close (struct file*) ; 
 int /*<<< orphan*/  ima_file_free (struct file*) ; 
 int /*<<< orphan*/  locks_remove_flock (struct file*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_file_free (struct file*) ; 
 int /*<<< orphan*/  stub1 (int,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct inode*,struct file*) ; 
 scalar_t__ unlikely (int) ; 

void __fput(struct file *file)
{
	struct dentry *dentry = file->f_path.dentry;
	struct vfsmount *mnt = file->f_path.mnt;
	struct inode *inode = dentry->d_inode;

	might_sleep();

	fsnotify_close(file);
	/*
	 * The function eventpoll_release() should be the first called
	 * in the file cleanup chain.
	 */
	eventpoll_release(file);
	locks_remove_flock(file);

	if (unlikely(file->f_flags & FASYNC)) {
		if (file->f_op && file->f_op->fasync)
			file->f_op->fasync(-1, file, 0);
	}
	if (file->f_op && file->f_op->release)
		file->f_op->release(inode, file);
	security_file_free(file);
	ima_file_free(file);
	if (unlikely(S_ISCHR(inode->i_mode) && inode->i_cdev != NULL))
		cdev_put(inode->i_cdev);
	fops_put(file->f_op);
	put_pid(file->f_owner.pid);
	file_kill(file);
	if (file->f_mode & FMODE_WRITE)
		drop_file_write_access(file);
	file->f_path.dentry = NULL;
	file->f_path.mnt = NULL;
	file_free(file);
	dput(dentry);
	mntput(mnt);
}