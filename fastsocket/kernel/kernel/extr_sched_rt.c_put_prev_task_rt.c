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
struct TYPE_4__ {int nr_cpus_allowed; } ;
struct TYPE_3__ {scalar_t__ on_rq; scalar_t__ exec_start; } ;
struct task_struct {TYPE_2__ rt; TYPE_1__ se; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enqueue_pushable_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  update_curr_rt (struct rq*) ; 

__attribute__((used)) static void put_prev_task_rt(struct rq *rq, struct task_struct *p)
{
	update_curr_rt(rq);
	p->se.exec_start = 0;

	/*
	 * The previous task needs to be made eligible for pushing
	 * if it is still active
	 */
	if (p->se.on_rq && p->rt.nr_cpus_allowed > 1)
		enqueue_pushable_task(rq, p);
}