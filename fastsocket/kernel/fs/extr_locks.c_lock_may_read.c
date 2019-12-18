#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {struct file_lock* i_flock; } ;
struct file_lock {int fl_type; scalar_t__ fl_end; scalar_t__ fl_start; struct file_lock* fl_next; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int F_RDLCK ; 
 scalar_t__ IS_FLOCK (struct file_lock*) ; 
 scalar_t__ IS_POSIX (struct file_lock*) ; 
 int LOCK_MAND ; 
 int LOCK_READ ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int lock_may_read(struct inode *inode, loff_t start, unsigned long len)
{
	struct file_lock *fl;
	int result = 1;
	lock_kernel();
	for (fl = inode->i_flock; fl != NULL; fl = fl->fl_next) {
		if (IS_POSIX(fl)) {
			if (fl->fl_type == F_RDLCK)
				continue;
			if ((fl->fl_end < start) || (fl->fl_start > (start + len)))
				continue;
		} else if (IS_FLOCK(fl)) {
			if (!(fl->fl_type & LOCK_MAND))
				continue;
			if (fl->fl_type & LOCK_READ)
				continue;
		} else
			continue;
		result = 0;
		break;
	}
	unlock_kernel();
	return result;
}