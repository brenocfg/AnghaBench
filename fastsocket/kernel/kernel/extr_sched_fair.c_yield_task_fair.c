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
struct sched_entity {int dummy; } ;
struct task_struct {scalar_t__ policy; struct sched_entity se; } ;
struct rq {int nr_running; struct task_struct* curr; } ;
struct cfs_rq {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCHED_BATCH ; 
 int /*<<< orphan*/  clear_buddies (struct cfs_rq*,struct sched_entity*) ; 
 int /*<<< orphan*/  set_skip_buddy (struct sched_entity*) ; 
 struct cfs_rq* task_cfs_rq (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_curr (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_rq_clock (struct rq*) ; 

__attribute__((used)) static void yield_task_fair(struct rq *rq)
{
	struct task_struct *curr = rq->curr;
	struct cfs_rq *cfs_rq = task_cfs_rq(curr);
	struct sched_entity *se = &curr->se;

	/*
	 * Are we the only task in the tree?
	 */
	if (unlikely(rq->nr_running == 1))
		return;

	clear_buddies(cfs_rq, se);

	if (curr->policy != SCHED_BATCH) {
		update_rq_clock(rq);
		/*
		 * Update run-time statistics of the 'current'.
		 */
		update_curr(cfs_rq);
	}

	set_skip_buddy(se);
}