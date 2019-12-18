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
struct sched_entity {int /*<<< orphan*/  on_rq; } ;
struct task_struct {scalar_t__ policy; struct sched_entity se; } ;
struct rq {struct task_struct* idle; struct task_struct* curr; } ;
struct cfs_rq {scalar_t__ nr_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LAST_BUDDY ; 
 int /*<<< orphan*/  NEXT_BUDDY ; 
 scalar_t__ SCHED_IDLE ; 
 scalar_t__ SCHED_NORMAL ; 
 int /*<<< orphan*/  WAKEUP_PREEMPT ; 
 int WF_FORK ; 
 int /*<<< orphan*/  cfs_rq_of (struct sched_entity*) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 int /*<<< orphan*/  find_matching_se (struct sched_entity**,struct sched_entity**) ; 
 int /*<<< orphan*/  resched_task (struct task_struct*) ; 
 scalar_t__ sched_feat (int /*<<< orphan*/ ) ; 
 scalar_t__ sched_nr_latency ; 
 int /*<<< orphan*/  set_last_buddy (struct sched_entity*) ; 
 int /*<<< orphan*/  set_next_buddy (struct sched_entity*) ; 
 struct cfs_rq* task_cfs_rq (struct task_struct*) ; 
 scalar_t__ test_tsk_need_resched (struct task_struct*) ; 
 int throttled_hierarchy (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int wakeup_preempt_entity (struct sched_entity*,struct sched_entity*) ; 

__attribute__((used)) static void check_preempt_wakeup(struct rq *rq, struct task_struct *p, int wake_flags)
{
	struct task_struct *curr = rq->curr;
	struct sched_entity *se = &curr->se, *pse = &p->se;
	struct cfs_rq *cfs_rq = task_cfs_rq(curr);
	int scale = cfs_rq->nr_running >= sched_nr_latency;
	int next_buddy_marked = 0;

	if (unlikely(se == pse))
		return;

	/*
 	 * This is possible from callers such as pull_task(), in which we
	 * unconditionally check_prempt_curr() after an enqueue (which may have
	 * lead to a throttle).  This both saves work and prevents false
	 * next-buddy nomination below.
	 */
	if (unlikely(throttled_hierarchy(cfs_rq_of(pse))))
		return;

	if (sched_feat(NEXT_BUDDY) && scale && !(wake_flags & WF_FORK)) {
		set_next_buddy(pse);
		next_buddy_marked = 1;
	}

	/*
	 * We can come here with TIF_NEED_RESCHED already set from new task
	 * wake up path.
	 *
	 * Note: this also catches the edge-case of curr being in a throttled
	 * group (e.g. via set_curr_task), since update_curr() (in the
	 * enqueue of curr) will have resulted in resched being set.  This
	 * prevents us from potentially nominating it as a false LAST_BUDDY
	 * below.
	 */
	if (test_tsk_need_resched(curr))
		return;

	/*
	 * Batch and idle tasks do not preempt (their preemption is driven by
	 * the tick):
	 */
	if (unlikely(p->policy != SCHED_NORMAL))
		return;

	/* Idle tasks are by definition preempted by everybody. */
	if (unlikely(curr->policy == SCHED_IDLE))
		goto preempt;

	if (!sched_feat(WAKEUP_PREEMPT))
		return;

	update_curr(cfs_rq);
	find_matching_se(&se, &pse);
	BUG_ON(!pse);
	if (wakeup_preempt_entity(se, pse) == 1) {
		/*
		 * Bias pick_next to pick the sched entity that is
		 * triggering this preemption.
		 */
		if (!next_buddy_marked)
			set_next_buddy(pse);
		goto preempt;
	}

	return;

preempt:
	resched_task(curr);
	/*
	 * Only set the backward buddy when the current task is still
	 * on the rq. This can happen when a wakeup gets interleaved
	 * with schedule on the ->pre_schedule() or idle_balance()
	 * point, either of which can * drop the rq lock.
	 *
	 * Also, during early boot the idle thread is in the fair class,
	 * for obvious reasons its a bad idea to schedule back to it.
	 */
	if (unlikely(!se->on_rq || curr == rq->idle))
		return;

	if (sched_feat(LAST_BUDDY) && scale && entity_is_task(se))
		set_last_buddy(se);
}