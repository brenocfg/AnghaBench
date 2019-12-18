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
struct sched_rt_entity {int dummy; } ;
struct task_struct {struct sched_rt_entity rt; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_nr_running (struct rq*) ; 
 int /*<<< orphan*/  dequeue_pushable_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  dequeue_rt_entity (struct sched_rt_entity*) ; 
 int /*<<< orphan*/  update_curr_rt (struct rq*) ; 

__attribute__((used)) static void dequeue_task_rt(struct rq *rq, struct task_struct *p, int flags)
{
	struct sched_rt_entity *rt_se = &p->rt;

	update_curr_rt(rq);
	dequeue_rt_entity(rt_se);

	dequeue_pushable_task(rq, p);

	dec_nr_running(rq);
}