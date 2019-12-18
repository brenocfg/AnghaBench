#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {scalar_t__ prio; } ;
struct TYPE_3__ {scalar_t__ overloaded; } ;
struct rq {TYPE_2__* curr; TYPE_1__ rt; } ;
struct TYPE_4__ {scalar_t__ prio; } ;

/* Variables and functions */
 scalar_t__ push_rt_task (struct rq*) ; 
 int /*<<< orphan*/  resched_task (TYPE_2__*) ; 
 struct rq* task_rq (struct task_struct*) ; 

__attribute__((used)) static void switched_to_rt(struct rq *rq, struct task_struct *p,
			   int running)
{
	int check_resched = 1;

	/*
	 * If we are already running, then there's nothing
	 * that needs to be done. But if we are not running
	 * we may need to preempt the current running task.
	 * If that current running task is also an RT task
	 * then see if we can move to another run queue.
	 */
	if (!running) {
#ifdef CONFIG_SMP
		if (rq->rt.overloaded && push_rt_task(rq) &&
		    /* Don't resched if we changed runqueues */
		    rq != task_rq(p))
			check_resched = 0;
#endif /* CONFIG_SMP */
		if (check_resched && p->prio < rq->curr->prio)
			resched_task(rq->curr);
	}
}