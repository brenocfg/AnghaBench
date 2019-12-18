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
struct task_struct {TYPE_1__* sched_class; int /*<<< orphan*/  state; } ;
struct rq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* task_woken ) (struct rq*,struct task_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BALANCE_FORK ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_WAKING ; 
 int /*<<< orphan*/  WF_FORK ; 
 int /*<<< orphan*/  activate_task (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_preempt_curr (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int select_task_rq (struct rq*,struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_task_cpu (struct task_struct*,int) ; 
 int /*<<< orphan*/  stub1 (struct rq*,struct task_struct*) ; 
 struct rq* task_rq_lock (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  task_rq_unlock (struct rq*,unsigned long*) ; 
 int /*<<< orphan*/  trace_sched_wakeup_new (struct rq*,struct task_struct*,int) ; 

void wake_up_new_task(struct task_struct *p, unsigned long clone_flags)
{
	unsigned long flags;
	struct rq *rq;
	int cpu = get_cpu();

#ifdef CONFIG_SMP
	rq = task_rq_lock(p, &flags);
	p->state = TASK_WAKING;

	/*
	 * Fork balancing, do it here and not earlier because:
	 *  - cpus_allowed can change in the fork path
	 *  - any previously selected cpu might disappear through hotplug
	 *
	 * We set TASK_WAKING so that select_task_rq() can drop rq->lock
	 * without people poking at ->cpus_allowed.
	 */
	cpu = select_task_rq(rq, p, SD_BALANCE_FORK, 0);
	set_task_cpu(p, cpu);

	p->state = TASK_RUNNING;
	task_rq_unlock(rq, &flags);
#endif

	rq = task_rq_lock(p, &flags);
	activate_task(rq, p, 0);
	trace_sched_wakeup_new(rq, p, 1);
	check_preempt_curr(rq, p, WF_FORK);
#ifdef CONFIG_SMP
	if (p->sched_class->task_woken)
		p->sched_class->task_woken(rq, p);
#endif
	task_rq_unlock(rq, &flags);
	put_cpu();
}