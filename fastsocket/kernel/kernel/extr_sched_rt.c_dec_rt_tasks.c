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
 int /*<<< orphan*/  dec_rt_group (struct sched_rt_entity*,struct rt_rq*) ; 
 int /*<<< orphan*/  dec_rt_migration (struct sched_rt_entity*,struct rt_rq*) ; 
 int /*<<< orphan*/  dec_rt_prio (struct rt_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_prio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_se_prio (struct sched_rt_entity*) ; 

__attribute__((used)) static inline
void dec_rt_tasks(struct sched_rt_entity *rt_se, struct rt_rq *rt_rq)
{
	WARN_ON(!rt_prio(rt_se_prio(rt_se)));
	WARN_ON(!rt_rq->rt_nr_running);
	rt_rq->rt_nr_running--;

	dec_rt_prio(rt_rq, rt_se_prio(rt_se));
	dec_rt_migration(rt_se, rt_rq);
	dec_rt_group(rt_se, rt_rq);
}