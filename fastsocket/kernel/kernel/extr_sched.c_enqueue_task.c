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
struct TYPE_4__ {int on_rq; } ;
struct task_struct {TYPE_2__ se; TYPE_1__* sched_class; } ;
struct rq {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enqueue_task ) (struct rq*,struct task_struct*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sched_info_queued (struct task_struct*) ; 
 int /*<<< orphan*/  stub1 (struct rq*,struct task_struct*,int) ; 
 int /*<<< orphan*/  update_rq_clock (struct rq*) ; 

__attribute__((used)) static void enqueue_task(struct rq *rq, struct task_struct *p, int flags)
{
	update_rq_clock(rq);
	sched_info_queued(p);
	p->sched_class->enqueue_task(rq, p, flags);
	p->se.on_rq = 1;
}