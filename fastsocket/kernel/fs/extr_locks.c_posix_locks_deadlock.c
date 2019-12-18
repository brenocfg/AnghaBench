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
 int /*<<< orphan*/  MAX_DEADLK_ITERATIONS ; 
 scalar_t__ posix_same_owner (struct file_lock*,struct file_lock*) ; 
 struct file_lock* what_owner_is_waiting_for (struct file_lock*) ; 

__attribute__((used)) static int posix_locks_deadlock(struct file_lock *caller_fl,
				struct file_lock *block_fl)
{
	int i = 0;

	while ((block_fl = what_owner_is_waiting_for(block_fl))) {
		if (i++ > MAX_DEADLK_ITERATIONS)
			return 0;
		if (posix_same_owner(caller_fl, block_fl))
			return 1;
	}
	return 0;
}