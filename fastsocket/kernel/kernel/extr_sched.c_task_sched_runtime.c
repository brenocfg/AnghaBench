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
typedef  unsigned long long u64 ;
struct TYPE_2__ {unsigned long long sum_exec_runtime; } ;
struct task_struct {TYPE_1__ se; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 unsigned long long do_task_delta_exec (struct task_struct*,struct rq*) ; 
 struct rq* task_rq_lock (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  task_rq_unlock (struct rq*,unsigned long*) ; 

unsigned long long task_sched_runtime(struct task_struct *p)
{
	unsigned long flags;
	struct rq *rq;
	u64 ns = 0;

	rq = task_rq_lock(p, &flags);
	ns = p->se.sum_exec_runtime + do_task_delta_exec(p, rq);
	task_rq_unlock(rq, &flags);

	return ns;
}