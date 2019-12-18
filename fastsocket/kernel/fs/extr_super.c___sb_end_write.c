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
struct TYPE_2__ {int /*<<< orphan*/ * lock_map; int /*<<< orphan*/  wait; int /*<<< orphan*/ * counter; } ;
struct super_block {TYPE_1__ s_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwsem_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_has_new_freeze (struct super_block*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void __sb_end_write(struct super_block *sb, int level)
{
	/* Out of tree modules don't use this mechanism */
	if (unlikely(!sb_has_new_freeze(sb)))
		return;

	percpu_counter_dec(&sb->s_writers.counter[level-1]);
	/*
	 * Make sure s_writers are updated before we wake up waiters in
	 * freeze_super().
	 */
	smp_mb();
	if (waitqueue_active(&sb->s_writers.wait))
		wake_up(&sb->s_writers.wait);
	rwsem_release(&sb->s_writers.lock_map[level-1], 1, _RET_IP_);
}