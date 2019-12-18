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
struct file_lock {int fl_flags; int /*<<< orphan*/  fl_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FL_FLOCK 129 
#define  FL_POSIX 128 
 int flock_lock_file_wait (int /*<<< orphan*/ ,struct file_lock*) ; 
 int posix_lock_file_wait (int /*<<< orphan*/ ,struct file_lock*) ; 

__attribute__((used)) static int do_vfs_lock(struct file_lock *fl)
{
	int res = 0;
	switch (fl->fl_flags & (FL_POSIX|FL_FLOCK)) {
		case FL_POSIX:
			res = posix_lock_file_wait(fl->fl_file, fl);
			break;
		case FL_FLOCK:
			res = flock_lock_file_wait(fl->fl_file, fl);
			break;
		default:
			BUG();
	}
	return res;
}