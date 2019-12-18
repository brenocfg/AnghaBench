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
struct tty_struct {int minimum_to_wake; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  fasync; int /*<<< orphan*/  ctrl_lock; struct pid* pgrp; } ;
struct pid {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; scalar_t__ private_data; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int N_TTY_BUF_SIZE ; 
 int PIDTYPE_PGID ; 
 int PIDTYPE_PID ; 
 int __f_setown (struct file*,struct pid*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_pid (struct pid*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pid* task_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ tty_paranoia_check (struct tty_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_fasync(int fd, struct file *filp, int on)
{
	struct tty_struct *tty;
	unsigned long flags;
	int retval = 0;

	lock_kernel();
	tty = (struct tty_struct *)filp->private_data;
	if (tty_paranoia_check(tty, filp->f_path.dentry->d_inode, "tty_fasync"))
		goto out;

	retval = fasync_helper(fd, filp, on, &tty->fasync);
	if (retval <= 0)
		goto out;

	if (on) {
		enum pid_type type;
		struct pid *pid;
		if (!waitqueue_active(&tty->read_wait))
			tty->minimum_to_wake = 1;
		spin_lock_irqsave(&tty->ctrl_lock, flags);
		if (tty->pgrp) {
			pid = tty->pgrp;
			type = PIDTYPE_PGID;
		} else {
			pid = task_pid(current);
			type = PIDTYPE_PID;
		}
		get_pid(pid);
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		retval = __f_setown(filp, pid, type, 0);
		put_pid(pid);
		if (retval)
			goto out;
	} else {
		if (!tty->fasync && !waitqueue_active(&tty->read_wait))
			tty->minimum_to_wake = N_TTY_BUF_SIZE;
	}
	retval = 0;
out:
	unlock_kernel();
	return retval;
}