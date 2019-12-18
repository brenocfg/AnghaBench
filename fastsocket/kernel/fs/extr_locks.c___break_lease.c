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
struct inode {struct file_lock* i_flock; } ;
struct file_lock {scalar_t__ fl_owner; int fl_type; unsigned long fl_break_time; struct file_lock* fl_next; int /*<<< orphan*/  fl_wait; TYPE_1__* fl_lmops; } ;
struct TYPE_4__ {scalar_t__ files; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fl_break ) (struct file_lock*) ;} ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int F_INPROGRESS ; 
 int F_RDLCK ; 
 int F_UNLCK ; 
 int F_WRLCK ; 
 unsigned long HZ ; 
 scalar_t__ IS_ERR (struct file_lock*) ; 
 scalar_t__ IS_LEASE (struct file_lock*) ; 
 unsigned int O_ACCMODE ; 
 unsigned int O_NONBLOCK ; 
 unsigned int O_RDONLY ; 
 int PTR_ERR (struct file_lock*) ; 
 int /*<<< orphan*/  __locks_delete_block (struct file_lock*) ; 
 TYPE_2__* current ; 
 unsigned long jiffies ; 
 struct file_lock* lease_alloc (int /*<<< orphan*/ *,int) ; 
 unsigned long lease_break_time ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  locks_free_lock (struct file_lock*) ; 
 int /*<<< orphan*/  locks_insert_block (struct file_lock*,struct file_lock*) ; 
 int /*<<< orphan*/  stub1 (struct file_lock*) ; 
 int /*<<< orphan*/  time_out_leases (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

int __break_lease(struct inode *inode, unsigned int mode)
{
	int error = 0, future;
	struct file_lock *new_fl, *flock;
	struct file_lock *fl;
	unsigned long break_time;
	int i_have_this_lease = 0;
	int want_write = (mode & O_ACCMODE) != O_RDONLY;

	new_fl = lease_alloc(NULL, want_write ? F_WRLCK : F_RDLCK);

	lock_kernel();

	time_out_leases(inode);

	flock = inode->i_flock;
	if ((flock == NULL) || !IS_LEASE(flock))
		goto out;

	for (fl = flock; fl && IS_LEASE(fl); fl = fl->fl_next)
		if (fl->fl_owner == current->files)
			i_have_this_lease = 1;

	if (want_write) {
		/* If we want write access, we have to revoke any lease. */
		future = F_UNLCK | F_INPROGRESS;
	} else if (flock->fl_type & F_INPROGRESS) {
		/* If the lease is already being broken, we just leave it */
		future = flock->fl_type;
	} else if (flock->fl_type & F_WRLCK) {
		/* Downgrade the exclusive lease to a read-only lease. */
		future = F_RDLCK | F_INPROGRESS;
	} else {
		/* the existing lease was read-only, so we can read too. */
		goto out;
	}

	if (IS_ERR(new_fl) && !i_have_this_lease
			&& ((mode & O_NONBLOCK) == 0)) {
		error = PTR_ERR(new_fl);
		goto out;
	}

	break_time = 0;
	if (lease_break_time > 0) {
		break_time = jiffies + lease_break_time * HZ;
		if (break_time == 0)
			break_time++;	/* so that 0 means no break time */
	}

	for (fl = flock; fl && IS_LEASE(fl); fl = fl->fl_next) {
		if (fl->fl_type != future) {
			fl->fl_type = future;
			fl->fl_break_time = break_time;
			/* lease must have lmops break callback */
			fl->fl_lmops->fl_break(fl);
		}
	}

	if (i_have_this_lease || (mode & O_NONBLOCK)) {
		error = -EWOULDBLOCK;
		goto out;
	}

restart:
	break_time = flock->fl_break_time;
	if (break_time != 0) {
		break_time -= jiffies;
		if (break_time == 0)
			break_time++;
	}
	locks_insert_block(flock, new_fl);
	error = wait_event_interruptible_timeout(new_fl->fl_wait,
						!new_fl->fl_next, break_time);
	__locks_delete_block(new_fl);
	if (error >= 0) {
		if (error == 0)
			time_out_leases(inode);
		/* Wait for the next lease that has not been broken yet */
		for (flock = inode->i_flock; flock && IS_LEASE(flock);
				flock = flock->fl_next) {
			if (flock->fl_type & F_INPROGRESS)
				goto restart;
		}
		error = 0;
	}

out:
	unlock_kernel();
	if (!IS_ERR(new_fl))
		locks_free_lock(new_fl);
	return error;
}