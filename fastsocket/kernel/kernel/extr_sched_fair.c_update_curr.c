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
typedef  scalar_t__ u64 ;
struct task_struct {int dummy; } ;
struct sched_entity {int /*<<< orphan*/  vruntime; scalar_t__ exec_start; } ;
struct cfs_rq {struct sched_entity* curr; } ;
struct TYPE_2__ {scalar_t__ clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __update_curr (struct cfs_rq*,struct sched_entity*,unsigned long) ; 
 int /*<<< orphan*/  account_cfs_rq_runtime (struct cfs_rq*,unsigned long) ; 
 int /*<<< orphan*/  account_group_exec_runtime (struct task_struct*,unsigned long) ; 
 int /*<<< orphan*/  cpuacct_charge (struct task_struct*,unsigned long) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 TYPE_1__* rq_of (struct cfs_rq*) ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 int /*<<< orphan*/  trace_sched_stat_runtime (struct task_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void update_curr(struct cfs_rq *cfs_rq)
{
	struct sched_entity *curr = cfs_rq->curr;
	u64 now = rq_of(cfs_rq)->clock;
	unsigned long delta_exec;

	if (unlikely(!curr))
		return;

	/*
	 * Get the amount of time the current task was running
	 * since the last time we changed load (this cannot
	 * overflow on 32 bits):
	 */
	delta_exec = (unsigned long)(now - curr->exec_start);
	if (!delta_exec)
		return;

	__update_curr(cfs_rq, curr, delta_exec);
	curr->exec_start = now;

	if (entity_is_task(curr)) {
		struct task_struct *curtask = task_of(curr);

		trace_sched_stat_runtime(curtask, delta_exec, curr->vruntime);
		cpuacct_charge(curtask, delta_exec);
		account_group_exec_runtime(curtask, delta_exec);
	}

	account_cfs_rq_runtime(cfs_rq, delta_exec);
}