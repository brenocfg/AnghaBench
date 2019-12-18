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
struct TYPE_2__ {int /*<<< orphan*/  weight; } ;
struct sched_entity {int /*<<< orphan*/  group_node; TYPE_1__ load; } ;
struct cfs_rq {int /*<<< orphan*/  nr_running; int /*<<< orphan*/  tasks; int /*<<< orphan*/  load; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_cfs_task_weight (struct cfs_rq*,int /*<<< orphan*/ ) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 int /*<<< orphan*/  inc_cpu_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_entity (struct sched_entity*) ; 
 int /*<<< orphan*/  rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  update_load_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
account_entity_enqueue(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	update_load_add(&cfs_rq->load, se->load.weight);
	if (!parent_entity(se))
		inc_cpu_load(rq_of(cfs_rq), se->load.weight);
	if (entity_is_task(se)) {
		add_cfs_task_weight(cfs_rq, se->load.weight);
		list_add(&se->group_node, &cfs_rq->tasks);
	}
	cfs_rq->nr_running++;
}