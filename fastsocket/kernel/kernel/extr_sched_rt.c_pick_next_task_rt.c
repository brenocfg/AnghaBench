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
struct task_struct {int dummy; } ;
struct rq {int /*<<< orphan*/  post_schedule; } ;

/* Variables and functions */
 struct task_struct* _pick_next_task_rt (struct rq*) ; 
 int /*<<< orphan*/  dequeue_pushable_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  has_pushable_tasks (struct rq*) ; 

__attribute__((used)) static struct task_struct *pick_next_task_rt(struct rq *rq)
{
	struct task_struct *p = _pick_next_task_rt(rq);

	/* The running task is never eligible for pushing */
	if (p)
		dequeue_pushable_task(rq, p);

#ifdef CONFIG_SMP
	/*
	 * We detect this state here so that we can avoid taking the RQ
	 * lock again later if there is no need to push
	 */
	rq->post_schedule = has_pushable_tasks(rq);
#endif

	return p;
}