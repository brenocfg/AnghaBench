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
struct inode {struct file_lock* i_flock; } ;
struct file_lock {scalar_t__ fl_owner; struct file_lock* fl_next; } ;
typedef  scalar_t__ fl_owner_t ;
struct TYPE_2__ {scalar_t__ files; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IS_POSIX (struct file_lock*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int locks_mandatory_locked(struct inode *inode)
{
	fl_owner_t owner = current->files;
	struct file_lock *fl;

	/*
	 * Search the lock list for this inode for any POSIX locks.
	 */
	lock_kernel();
	for (fl = inode->i_flock; fl != NULL; fl = fl->fl_next) {
		if (!IS_POSIX(fl))
			continue;
		if (fl->fl_owner != owner)
			break;
	}
	unlock_kernel();
	return fl ? -EAGAIN : 0;
}