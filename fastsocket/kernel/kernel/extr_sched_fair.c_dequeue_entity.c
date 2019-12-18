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
struct task_struct {int state; } ;
struct sched_entity {int /*<<< orphan*/  vruntime; scalar_t__ on_rq; int /*<<< orphan*/  block_start; int /*<<< orphan*/  sleep_start; } ;
struct cfs_rq {int /*<<< orphan*/  nr_running; scalar_t__ min_vruntime; struct sched_entity* curr; } ;
struct TYPE_2__ {int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int DEQUEUE_SLEEP ; 
 int TASK_INTERRUPTIBLE ; 
 int TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __dequeue_entity (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  account_entity_dequeue (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  clear_buddies (struct cfs_rq*,struct sched_entity*) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 int /*<<< orphan*/  return_cfs_rq_runtime (struct cfs_rq*) ; 
 TYPE_1__* rq_of (struct cfs_rq*) ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 int /*<<< orphan*/  update_cfs_load (struct cfs_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cfs_shares (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_min_vruntime (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_stats_dequeue (struct cfs_rq*,struct sched_entity*) ; 

__attribute__((used)) static void
dequeue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
{
	/*
	 * Update run-time statistics of the 'current'.
	 */
	update_curr(cfs_rq);

	update_stats_dequeue(cfs_rq, se);
	if (flags & DEQUEUE_SLEEP) {
#ifdef CONFIG_SCHEDSTATS
		if (entity_is_task(se)) {
			struct task_struct *tsk = task_of(se);

			if (tsk->state & TASK_INTERRUPTIBLE)
				se->sleep_start = rq_of(cfs_rq)->clock;
			if (tsk->state & TASK_UNINTERRUPTIBLE)
				se->block_start = rq_of(cfs_rq)->clock;
		}
#endif
	}

	clear_buddies(cfs_rq, se);

	if (se != cfs_rq->curr)
		__dequeue_entity(cfs_rq, se);
	se->on_rq = 0;
	update_cfs_load(cfs_rq, 0);
	account_entity_dequeue(cfs_rq, se);

	/*
	 * Normalize the entity after updating the min_vruntime because the
	 * update can refer to the ->curr item and we need to reflect this
	 * movement in our normalized position.
	 */
	if (!(flags & DEQUEUE_SLEEP))
		se->vruntime -= cfs_rq->min_vruntime;

	update_min_vruntime(cfs_rq);
	update_cfs_shares(cfs_rq);

	/* return excess runtime on last dequeue */
	if (!cfs_rq->nr_running)
		return_cfs_rq_runtime(cfs_rq);
}