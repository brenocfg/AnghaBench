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
struct TYPE_2__ {int /*<<< orphan*/  on_rq; } ;
struct task_struct {int policy; int rt_priority; int /*<<< orphan*/  prio; int /*<<< orphan*/  normal_prio; int /*<<< orphan*/ * sched_class; TYPE_1__ se; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
#define  SCHED_BATCH 132 
#define  SCHED_FIFO 131 
#define  SCHED_IDLE 130 
#define  SCHED_NORMAL 129 
#define  SCHED_RR 128 
 int /*<<< orphan*/  fair_sched_class ; 
 int /*<<< orphan*/  normal_prio (struct task_struct*) ; 
 int /*<<< orphan*/  rt_mutex_getprio (struct task_struct*) ; 
 int /*<<< orphan*/  rt_sched_class ; 
 int /*<<< orphan*/  set_load_weight (struct task_struct*) ; 

__attribute__((used)) static void
__setscheduler(struct rq *rq, struct task_struct *p, int policy, int prio)
{
	BUG_ON(p->se.on_rq);

	p->policy = policy;
	switch (p->policy) {
	case SCHED_NORMAL:
	case SCHED_BATCH:
	case SCHED_IDLE:
		p->sched_class = &fair_sched_class;
		break;
	case SCHED_FIFO:
	case SCHED_RR:
		p->sched_class = &rt_sched_class;
		break;
	}

	p->rt_priority = prio;
	p->normal_prio = normal_prio(p);
	/* we are holding p->pi_lock already */
	p->prio = rt_mutex_getprio(p);
	set_load_weight(p);
}