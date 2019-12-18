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
struct TYPE_2__ {int /*<<< orphan*/  exec_start; } ;
struct task_struct {TYPE_1__ se; } ;
struct sched_rt_entity {int dummy; } ;
struct rt_rq {int /*<<< orphan*/  rt_nr_running; } ;
struct rq {int /*<<< orphan*/  clock; int /*<<< orphan*/  idle; struct rt_rq rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct rt_rq* group_rt_rq (struct sched_rt_entity*) ; 
 struct sched_rt_entity* pick_next_rt_entity (struct rq*,struct rt_rq*) ; 
 scalar_t__ rt_rq_throttled (struct rt_rq*) ; 
 struct task_struct* rt_task_of (struct sched_rt_entity*) ; 
 int /*<<< orphan*/  task_has_rt_policy (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct task_struct *_pick_next_task_rt(struct rq *rq)
{
	struct sched_rt_entity *rt_se;
	struct task_struct *p;
	struct rt_rq *rt_rq;

	rt_rq = &rq->rt;

	if (unlikely(!rt_rq->rt_nr_running))
		return NULL;

	if (rt_rq_throttled(rt_rq) && !task_has_rt_policy(rq->idle))
		return NULL;

	do {
		rt_se = pick_next_rt_entity(rq, rt_rq);
		BUG_ON(!rt_se);
		rt_rq = group_rt_rq(rt_se);
	} while (rt_rq);

	p = rt_task_of(rt_se);
	p->se.exec_start = rq->clock;

	return p;
}