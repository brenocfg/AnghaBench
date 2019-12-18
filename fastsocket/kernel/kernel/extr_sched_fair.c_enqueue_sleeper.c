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
typedef  int u64 ;
struct task_struct {scalar_t__ in_iowait; } ;
struct sched_entity {int sleep_start; int sleep_max; int sum_sleep_runtime; int block_start; int block_max; int iowait_sum; int /*<<< orphan*/  iowait_count; } ;
struct cfs_rq {int dummy; } ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {int clock; } ;

/* Variables and functions */
 scalar_t__ SLEEP_PROFILING ; 
 int /*<<< orphan*/  account_scheduler_latency (struct task_struct*,int,int) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 scalar_t__ get_wchan (struct task_struct*) ; 
 scalar_t__ prof_on ; 
 int /*<<< orphan*/  profile_hits (scalar_t__,void*,int) ; 
 TYPE_1__* rq_of (struct cfs_rq*) ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 int /*<<< orphan*/  trace_sched_stat_blocked (struct task_struct*,int) ; 
 int /*<<< orphan*/  trace_sched_stat_iowait (struct task_struct*,int) ; 
 int /*<<< orphan*/  trace_sched_stat_sleep (struct task_struct*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void enqueue_sleeper(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
#ifdef CONFIG_SCHEDSTATS
	struct task_struct *tsk = NULL;

	if (entity_is_task(se))
		tsk = task_of(se);

	if (se->sleep_start) {
		u64 delta = rq_of(cfs_rq)->clock - se->sleep_start;

		if ((s64)delta < 0)
			delta = 0;

		if (unlikely(delta > se->sleep_max))
			se->sleep_max = delta;

		se->sleep_start = 0;
		se->sum_sleep_runtime += delta;

		if (tsk) {
			account_scheduler_latency(tsk, delta >> 10, 1);
			trace_sched_stat_sleep(tsk, delta);
		}
	}
	if (se->block_start) {
		u64 delta = rq_of(cfs_rq)->clock - se->block_start;

		if ((s64)delta < 0)
			delta = 0;

		if (unlikely(delta > se->block_max))
			se->block_max = delta;

		se->block_start = 0;
		se->sum_sleep_runtime += delta;

		if (tsk) {
			if (tsk->in_iowait) {
				se->iowait_sum += delta;
				se->iowait_count++;
				trace_sched_stat_iowait(tsk, delta);
			}

			trace_sched_stat_blocked(tsk, delta);

			/*
			 * Blocking time is in units of nanosecs, so shift by
			 * 20 to get a milliseconds-range estimation of the
			 * amount of time that the task spent sleeping:
			 */
			if (unlikely(prof_on == SLEEP_PROFILING)) {
				profile_hits(SLEEP_PROFILING,
						(void *)get_wchan(tsk),
						delta >> 20);
			}
			account_scheduler_latency(tsk, delta >> 10, 0);
		}
	}
#endif
}