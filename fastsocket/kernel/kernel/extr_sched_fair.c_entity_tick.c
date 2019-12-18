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
struct sched_entity {int dummy; } ;
struct cfs_rq {int nr_running; } ;
struct TYPE_2__ {int /*<<< orphan*/  hrtick_timer; int /*<<< orphan*/  curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOUBLE_TICK ; 
 int /*<<< orphan*/  WAKEUP_PREEMPT ; 
 int /*<<< orphan*/  check_preempt_tick (struct cfs_rq*,struct sched_entity*) ; 
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resched_task (int /*<<< orphan*/ ) ; 
 TYPE_1__* rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  sched_feat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_entity_shares_tick (struct cfs_rq*) ; 

__attribute__((used)) static void
entity_tick(struct cfs_rq *cfs_rq, struct sched_entity *curr, int queued)
{
	/*
	 * Update run-time statistics of the 'current'.
	 */
	update_curr(cfs_rq);

	/*
	 * Update share accounting for long-running entities.
	 */
	update_entity_shares_tick(cfs_rq);

#ifdef CONFIG_SCHED_HRTICK
	/*
	 * queued ticks are scheduled to match the slice, so don't bother
	 * validating it and just reschedule.
	 */
	if (queued) {
		resched_task(rq_of(cfs_rq)->curr);
		return;
	}
	/*
	 * don't let the period tick interfere with the hrtick preemption
	 */
	if (!sched_feat(DOUBLE_TICK) &&
			hrtimer_active(&rq_of(cfs_rq)->hrtick_timer))
		return;
#endif

	if (cfs_rq->nr_running > 1 || !sched_feat(WAKEUP_PREEMPT))
		check_preempt_tick(cfs_rq, curr);
}