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
struct file_lock {long fl_type; scalar_t__ fl_break_time; int /*<<< orphan*/  fl_fasync; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 long F_INPROGRESS ; 
 long F_UNLCK ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int __f_setown (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int fasync_helper (unsigned int,struct file*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int lease_init (struct file*,long,struct file_lock*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_out_leases (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int vfs_setlease (struct file*,long,struct file_lock**) ; 

int fcntl_setlease(unsigned int fd, struct file *filp, long arg)
{
	struct file_lock fl, *flp = &fl;
	struct inode *inode = filp->f_path.dentry->d_inode;
	int error;

	locks_init_lock(&fl);
	error = lease_init(filp, arg, &fl);
	if (error)
		return error;

	lock_kernel();

	error = vfs_setlease(filp, arg, &flp);
	if (error || arg == F_UNLCK)
		goto out_unlock;

	error = fasync_helper(fd, filp, 1, &flp->fl_fasync);
	if (error < 0) {
		/* remove lease just inserted by setlease */
		flp->fl_type = F_UNLCK | F_INPROGRESS;
		flp->fl_break_time = jiffies - 10;
		time_out_leases(inode);
		goto out_unlock;
	}

	error = __f_setown(filp, task_pid(current), PIDTYPE_PID, 0);
out_unlock:
	unlock_kernel();
	return error;
}