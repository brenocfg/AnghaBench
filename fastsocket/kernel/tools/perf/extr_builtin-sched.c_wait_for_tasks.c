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
typedef  int u64 ;
struct task_desc {scalar_t__ curr_event; int /*<<< orphan*/  sleep_sem; scalar_t__ cpu_usage; int /*<<< orphan*/  work_done_sem; int /*<<< orphan*/  ready_for_work; } ;
struct perf_sched {int cpu_usage; unsigned long nr_tasks; int runavg_cpu_usage; int parent_cpu_usage; int runavg_parent_cpu_usage; struct task_desc** tasks; int /*<<< orphan*/  start_work_mutex; int /*<<< orphan*/  work_done_wait_mutex; int /*<<< orphan*/  start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 int get_cpu_usage_nsec_parent () ; 
 int /*<<< orphan*/  get_nsecs () ; 
 unsigned long pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_for_tasks(struct perf_sched *sched)
{
	u64 cpu_usage_0, cpu_usage_1;
	struct task_desc *task;
	unsigned long i, ret;

	sched->start_time = get_nsecs();
	sched->cpu_usage = 0;
	pthread_mutex_unlock(&sched->work_done_wait_mutex);

	for (i = 0; i < sched->nr_tasks; i++) {
		task = sched->tasks[i];
		ret = sem_wait(&task->ready_for_work);
		BUG_ON(ret);
		sem_init(&task->ready_for_work, 0, 0);
	}
	ret = pthread_mutex_lock(&sched->work_done_wait_mutex);
	BUG_ON(ret);

	cpu_usage_0 = get_cpu_usage_nsec_parent();

	pthread_mutex_unlock(&sched->start_work_mutex);

	for (i = 0; i < sched->nr_tasks; i++) {
		task = sched->tasks[i];
		ret = sem_wait(&task->work_done_sem);
		BUG_ON(ret);
		sem_init(&task->work_done_sem, 0, 0);
		sched->cpu_usage += task->cpu_usage;
		task->cpu_usage = 0;
	}

	cpu_usage_1 = get_cpu_usage_nsec_parent();
	if (!sched->runavg_cpu_usage)
		sched->runavg_cpu_usage = sched->cpu_usage;
	sched->runavg_cpu_usage = (sched->runavg_cpu_usage * 9 + sched->cpu_usage) / 10;

	sched->parent_cpu_usage = cpu_usage_1 - cpu_usage_0;
	if (!sched->runavg_parent_cpu_usage)
		sched->runavg_parent_cpu_usage = sched->parent_cpu_usage;
	sched->runavg_parent_cpu_usage = (sched->runavg_parent_cpu_usage * 9 +
					 sched->parent_cpu_usage)/10;

	ret = pthread_mutex_lock(&sched->start_work_mutex);
	BUG_ON(ret);

	for (i = 0; i < sched->nr_tasks; i++) {
		task = sched->tasks[i];
		sem_init(&task->sleep_sem, 0, 0);
		task->curr_event = 0;
	}
}