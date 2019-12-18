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
struct TYPE_2__ {int /*<<< orphan*/  wait; int /*<<< orphan*/ * counter; int /*<<< orphan*/ * lock_map; } ;
struct super_block {TYPE_1__ s_writers; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  _THIS_IP_ ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_has_new_freeze (struct super_block*) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait ; 

void sb_wait_write(struct super_block *sb, int level)
{
	s64 writers;

	/* Out of tree modules don't use this mechanism */
	if (unlikely(!sb_has_new_freeze(sb)))
		return;
	/*
	 * We just cycle-through lockdep here so that it does not complain
	 * about returning with lock to userspace
	 */
	rwsem_acquire(&sb->s_writers.lock_map[level-1], 0, 0, _THIS_IP_);
	rwsem_release(&sb->s_writers.lock_map[level-1], 1, _THIS_IP_);

	do {
		DEFINE_WAIT(wait);

		/*
		 * We use a barrier in prepare_to_wait() to separate setting
		 * of frozen and checking of the counter
		 */
		prepare_to_wait(&sb->s_writers.wait, &wait,
				TASK_UNINTERRUPTIBLE);

		writers = percpu_counter_sum(&sb->s_writers.counter[level-1]);
		if (writers)
			schedule();

		finish_wait(&sb->s_writers.wait, &wait);
	} while (writers);
}