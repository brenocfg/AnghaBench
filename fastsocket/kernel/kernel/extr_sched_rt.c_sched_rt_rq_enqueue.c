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
struct rt_rq {scalar_t__ rt_nr_running; } ;
struct TYPE_2__ {int /*<<< orphan*/  curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  resched_task (int /*<<< orphan*/ ) ; 
 TYPE_1__* rq_of_rt_rq (struct rt_rq*) ; 

__attribute__((used)) static inline void sched_rt_rq_enqueue(struct rt_rq *rt_rq)
{
	if (rt_rq->rt_nr_running)
		resched_task(rq_of_rt_rq(rt_rq)->curr);
}