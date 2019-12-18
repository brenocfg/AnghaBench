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
struct timespec {int dummy; } ;
struct inode {struct timespec i_mtime; int /*<<< orphan*/  i_sb; struct file_lock* i_flock; } ;
struct file_lock {int fl_type; } ;

/* Variables and functions */
 int F_WRLCK ; 
 scalar_t__ IS_LEASE (struct file_lock*) ; 
 struct timespec current_fs_time (int /*<<< orphan*/ ) ; 

void lease_get_mtime(struct inode *inode, struct timespec *time)
{
	struct file_lock *flock = inode->i_flock;
	if (flock && IS_LEASE(flock) && (flock->fl_type & F_WRLCK))
		*time = current_fs_time(inode->i_sb);
	else
		*time = inode->i_mtime;
}