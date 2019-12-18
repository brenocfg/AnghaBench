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
struct TYPE_2__ {int on_rq; } ;
struct task_struct {int prio; void* static_prio; TYPE_1__ se; } ;
struct rq {int /*<<< orphan*/  curr; } ;

/* Variables and functions */
 void* NICE_TO_PRIO (long) ; 
 long TASK_NICE (struct task_struct*) ; 
 int /*<<< orphan*/  dequeue_task (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int effective_prio (struct task_struct*) ; 
 int /*<<< orphan*/  enqueue_task (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resched_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_load_weight (struct task_struct*) ; 
 scalar_t__ task_has_rt_policy (struct task_struct*) ; 
 struct rq* task_rq_lock (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  task_rq_unlock (struct rq*,unsigned long*) ; 
 scalar_t__ task_running (struct rq*,struct task_struct*) ; 

void set_user_nice(struct task_struct *p, long nice)
{
	int old_prio, delta, on_rq;
	unsigned long flags;
	struct rq *rq;

	if (TASK_NICE(p) == nice || nice < -20 || nice > 19)
		return;
	/*
	 * We have to be careful, if called from sys_setpriority(),
	 * the task might be in the middle of scheduling on another CPU.
	 */
	rq = task_rq_lock(p, &flags);
	/*
	 * The RT priorities are set via sched_setscheduler(), but we still
	 * allow the 'normal' nice value to be set - but as expected
	 * it wont have any effect on scheduling until the task is
	 * SCHED_FIFO/SCHED_RR:
	 */
	if (task_has_rt_policy(p)) {
		p->static_prio = NICE_TO_PRIO(nice);
		goto out_unlock;
	}
	on_rq = p->se.on_rq;
	if (on_rq)
		dequeue_task(rq, p, 0);

	p->static_prio = NICE_TO_PRIO(nice);
	set_load_weight(p);
	old_prio = p->prio;
	p->prio = effective_prio(p);
	delta = p->prio - old_prio;

	if (on_rq) {
		enqueue_task(rq, p, 0);
		/*
		 * If the task increased its priority or is running and
		 * lowered its priority, then reschedule its CPU:
		 */
		if (delta < 0 || (delta > 0 && task_running(rq, p)))
			resched_task(rq->curr);
	}
out_unlock:
	task_rq_unlock(rq, &flags);
}