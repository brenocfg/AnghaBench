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
struct inode {scalar_t__ i_ino; int i_state; TYPE_2__* i_sb; int /*<<< orphan*/  i_writecount; } ;
struct TYPE_4__ {TYPE_3__* dentry; } ;
struct file {TYPE_1__ f_path; } ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_6__ {struct inode* d_inode; } ;
struct TYPE_5__ {scalar_t__ s_dev; } ;

/* Variables and functions */
 int I_DIRTY ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int vfs_fsync (struct file*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_for_concurrent_writes(struct file *file)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	static ino_t last_ino;
	static dev_t last_dev;
	int err = 0;

	if (atomic_read(&inode->i_writecount) > 1
	    || (last_ino == inode->i_ino && last_dev == inode->i_sb->s_dev)) {
		dprintk("nfsd: write defer %d\n", task_pid_nr(current));
		msleep(10);
		dprintk("nfsd: write resume %d\n", task_pid_nr(current));
	}

	if (inode->i_state & I_DIRTY) {
		dprintk("nfsd: write sync %d\n", task_pid_nr(current));
		err = vfs_fsync(file, file->f_path.dentry, 0);
	}
	last_ino = inode->i_ino;
	last_dev = inode->i_sb->s_dev;
	return err;
}