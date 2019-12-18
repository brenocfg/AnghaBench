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
struct task_struct {struct sched_class const* sched_class; } ;
struct sched_class {int /*<<< orphan*/  (* prio_changed ) (struct rq*,struct task_struct*,int,int) ;int /*<<< orphan*/  (* switched_to ) (struct rq*,struct task_struct*,int) ;int /*<<< orphan*/  (* switched_from ) (struct rq*,struct task_struct*,int) ;} ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sched_autogroup_move_task (struct task_struct*) ; 
 int /*<<< orphan*/  stub1 (struct rq*,struct task_struct*,int) ; 
 int /*<<< orphan*/  stub2 (struct rq*,struct task_struct*,int) ; 
 int /*<<< orphan*/  stub3 (struct rq*,struct task_struct*,int,int) ; 

__attribute__((used)) static inline void check_class_changed(struct rq *rq, struct task_struct *p,
				       const struct sched_class *prev_class,
				       int oldprio, int running)
{
	if (prev_class != p->sched_class) {
		/*
		 * If autogroup is enabled, it might happen that a task changed
		 * class from SCHED_OTHER to SCHED_RR or SCHED_FIFO and became
		 * RT task. In that case, move the group.
		 */
		sched_autogroup_move_task(p);

		if (prev_class->switched_from)
			prev_class->switched_from(rq, p, running);
		p->sched_class->switched_to(rq, p, running);
	} else
		p->sched_class->prio_changed(rq, p, oldprio, running);
}