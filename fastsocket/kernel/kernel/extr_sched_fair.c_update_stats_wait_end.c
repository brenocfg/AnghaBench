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
struct sched_entity {scalar_t__ wait_start; scalar_t__ wait_sum; scalar_t__ wait_count; scalar_t__ wait_max; } ;
struct cfs_rq {int dummy; } ;
struct TYPE_2__ {scalar_t__ clock; } ;

/* Variables and functions */
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 TYPE_1__* rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  schedstat_set (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  task_of (struct sched_entity*) ; 
 int /*<<< orphan*/  trace_sched_stat_wait (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
update_stats_wait_end(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	schedstat_set(se->wait_max, max(se->wait_max,
			rq_of(cfs_rq)->clock - se->wait_start));
	schedstat_set(se->wait_count, se->wait_count + 1);
	schedstat_set(se->wait_sum, se->wait_sum +
			rq_of(cfs_rq)->clock - se->wait_start);
#ifdef CONFIG_SCHEDSTATS
	if (entity_is_task(se)) {
		trace_sched_stat_wait(task_of(se),
			rq_of(cfs_rq)->clock - se->wait_start);
	}
#endif
	schedstat_set(se->wait_start, 0);
}