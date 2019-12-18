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
struct sched_rt_entity {int dummy; } ;
struct TYPE_3__ {int curr; } ;
struct rt_rq {TYPE_1__ highest_prio; } ;
struct TYPE_4__ {int prio; } ;

/* Variables and functions */
 struct rt_rq* group_rt_rq (struct sched_rt_entity*) ; 
 TYPE_2__* rt_task_of (struct sched_rt_entity*) ; 

__attribute__((used)) static inline int rt_se_prio(struct sched_rt_entity *rt_se)
{
#ifdef CONFIG_RT_GROUP_SCHED
	struct rt_rq *rt_rq = group_rt_rq(rt_se);

	if (rt_rq)
		return rt_rq->highest_prio.curr;
#endif

	return rt_task_of(rt_se)->prio;
}