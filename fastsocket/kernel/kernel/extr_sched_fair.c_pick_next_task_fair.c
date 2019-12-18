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
struct task_struct {int dummy; } ;
struct sched_entity {int dummy; } ;
struct cfs_rq {int /*<<< orphan*/  nr_running; } ;
struct rq {struct cfs_rq cfs; } ;

/* Variables and functions */
 struct cfs_rq* group_cfs_rq (struct sched_entity*) ; 
 int /*<<< orphan*/  hrtick_start_fair (struct rq*,struct task_struct*) ; 
 struct sched_entity* pick_next_entity (struct cfs_rq*) ; 
 int /*<<< orphan*/  set_next_entity (struct cfs_rq*,struct sched_entity*) ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct task_struct *pick_next_task_fair(struct rq *rq)
{
	struct task_struct *p;
	struct cfs_rq *cfs_rq = &rq->cfs;
	struct sched_entity *se;

	if (unlikely(!cfs_rq->nr_running))
		return NULL;

	do {
		se = pick_next_entity(cfs_rq);
		set_next_entity(cfs_rq, se);
		cfs_rq = group_cfs_rq(se);
	} while (cfs_rq);

	p = task_of(se);
	hrtick_start_fair(rq, p);

	return p;
}