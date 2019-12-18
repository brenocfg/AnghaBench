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
struct rt_rq {int /*<<< orphan*/  rt_nr_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  inc_rt_group (struct sched_rt_entity*,struct rt_rq*) ; 
 int /*<<< orphan*/  inc_rt_migration (struct sched_rt_entity*,struct rt_rq*) ; 
 int /*<<< orphan*/  inc_rt_prio (struct rt_rq*,int) ; 
 int /*<<< orphan*/  rt_prio (int) ; 
 int rt_se_prio (struct sched_rt_entity*) ; 

__attribute__((used)) static inline
void inc_rt_tasks(struct sched_rt_entity *rt_se, struct rt_rq *rt_rq)
{
	int prio = rt_se_prio(rt_se);

	WARN_ON(!rt_prio(prio));
	rt_rq->rt_nr_running++;

	inc_rt_prio(rt_rq, prio);
	inc_rt_migration(rt_se, rt_rq);
	inc_rt_group(rt_se, rt_rq);
}