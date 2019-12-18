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
struct TYPE_2__ {int frozen; int /*<<< orphan*/ * counter; int /*<<< orphan*/  wait_unfrozen; } ;
struct super_block {TYPE_1__ s_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __sb_end_write (struct super_block*,int) ; 
 int /*<<< orphan*/  acquire_freeze_lock (struct super_block*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_has_new_freeze (struct super_block*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int __sb_start_write(struct super_block *sb, int level, bool wait)
{
	/* Out of tree modules don't use this mechanism */
	if (unlikely(!sb_has_new_freeze(sb)))
		return 1;
retry:
	if (unlikely(sb->s_writers.frozen >= level)) {
		if (!wait)
			return 0;
		wait_event(sb->s_writers.wait_unfrozen,
			   sb->s_writers.frozen < level);
	}

#ifdef CONFIG_LOCKDEP
	acquire_freeze_lock(sb, level, !wait, _RET_IP_);
#endif
	percpu_counter_inc(&sb->s_writers.counter[level-1]);
	/*
	 * Make sure counter is updated before we check for frozen.
	 * freeze_super() first sets frozen and then checks the counter.
	 */
	smp_mb();
	if (unlikely(sb->s_writers.frozen >= level)) {
		__sb_end_write(sb, level);
		goto retry;
	}
	return 1;
}