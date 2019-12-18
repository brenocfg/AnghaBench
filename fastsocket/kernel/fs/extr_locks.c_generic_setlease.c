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
struct inode {scalar_t__ i_uid; struct file_lock* i_flock; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_writecount; int /*<<< orphan*/  i_mode; } ;
struct file_lock {long fl_type; TYPE_2__* fl_lmops; struct file_lock* fl_next; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int /*<<< orphan*/  d_count; struct inode* d_inode; } ;
struct TYPE_4__ {int (* fl_change ) (struct file_lock**,long) ;scalar_t__ (* fl_mylease ) (struct file_lock*,struct file_lock*) ;int /*<<< orphan*/  fl_break; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CAP_LEASE ; 
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 long F_INPROGRESS ; 
 long F_RDLCK ; 
 long F_UNLCK ; 
 long F_WRLCK ; 
 scalar_t__ IS_LEASE (struct file_lock*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_fsuid () ; 
 int /*<<< orphan*/  leases_enable ; 
 struct file_lock* locks_alloc_lock () ; 
 int /*<<< orphan*/  locks_copy_lock (struct file_lock*,struct file_lock*) ; 
 int /*<<< orphan*/  locks_free_lock (struct file_lock*) ; 
 int /*<<< orphan*/  locks_insert_lock (struct file_lock**,struct file_lock*) ; 
 int security_file_lock (struct file*,long) ; 
 scalar_t__ stub1 (struct file_lock*,struct file_lock*) ; 
 int stub2 (struct file_lock**,long) ; 
 int /*<<< orphan*/  time_out_leases (struct inode*) ; 

int generic_setlease(struct file *filp, long arg, struct file_lock **flp)
{
	struct file_lock *fl, **before, **my_before = NULL, *lease;
	struct file_lock *new_fl = NULL;
	struct dentry *dentry = filp->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	int error, rdlease_count = 0, wrlease_count = 0;

	if ((current_fsuid() != inode->i_uid) && !capable(CAP_LEASE))
		return -EACCES;
	if (!S_ISREG(inode->i_mode))
		return -EINVAL;
	error = security_file_lock(filp, arg);
	if (error)
		return error;

	time_out_leases(inode);

	BUG_ON(!(*flp)->fl_lmops->fl_break);

	lease = *flp;

	if (arg != F_UNLCK) {
		error = -ENOMEM;
		new_fl = locks_alloc_lock();
		if (new_fl == NULL)
			goto out;

		error = -EAGAIN;
		if ((arg == F_RDLCK) && (atomic_read(&inode->i_writecount) > 0))
			goto out;
		if ((arg == F_WRLCK)
		    && ((atomic_read(&dentry->d_count) > 1)
			|| (atomic_read(&inode->i_count) > 1)))
			goto out;
	}

	/*
	 * At this point, we know that if there is an exclusive
	 * lease on this file, then we hold it on this filp
	 * (otherwise our open of this file would have blocked).
	 * And if we are trying to acquire an exclusive lease,
	 * then the file is not open by anyone (including us)
	 * except for this filp.
	 */
	for (before = &inode->i_flock;
			((fl = *before) != NULL) && IS_LEASE(fl);
			before = &fl->fl_next) {
		if (lease->fl_lmops->fl_mylease(fl, lease))
			my_before = before;
		else if (fl->fl_type == (F_INPROGRESS | F_UNLCK))
			/*
			 * Someone is in the process of opening this
			 * file for writing so we may not take an
			 * exclusive lease on it.
			 */
			wrlease_count++;
		else
			rdlease_count++;
	}

	error = -EAGAIN;
	if ((arg == F_RDLCK && (wrlease_count > 0)) ||
	    (arg == F_WRLCK && ((rdlease_count + wrlease_count) > 0)))
		goto out;

	if (my_before != NULL) {
		*flp = *my_before;
		error = lease->fl_lmops->fl_change(my_before, arg);
		goto out;
	}

	error = 0;
	if (arg == F_UNLCK)
		goto out;

	error = -EINVAL;
	if (!leases_enable)
		goto out;

	locks_copy_lock(new_fl, lease);
	locks_insert_lock(before, new_fl);

	*flp = new_fl;
	return 0;

out:
	if (new_fl != NULL)
		locks_free_lock(new_fl);
	return error;
}