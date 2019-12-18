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
struct file_lock {int dummy; } ;

/* Variables and functions */
 int F_UNLCK ; 
 int assign_type (struct file_lock*,int) ; 
 int /*<<< orphan*/  locks_delete_lock (struct file_lock**) ; 
 int /*<<< orphan*/  locks_wake_up_blocks (struct file_lock*) ; 

int lease_modify(struct file_lock **before, int arg)
{
	struct file_lock *fl = *before;
	int error = assign_type(fl, arg);

	if (error)
		return error;
	locks_wake_up_blocks(fl);
	if (arg == F_UNLCK)
		locks_delete_lock(before);
	return 0;
}