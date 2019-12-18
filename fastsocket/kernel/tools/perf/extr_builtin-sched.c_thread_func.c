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
typedef  scalar_t__ u64 ;
struct task_desc {char* comm; unsigned long nr_events; unsigned long curr_event; int /*<<< orphan*/  work_done_sem; scalar_t__ cpu_usage; int /*<<< orphan*/ * atoms; int /*<<< orphan*/  ready_for_work; } ;
struct sched_thread_parms {struct perf_sched* sched; struct task_desc* task; } ;
struct perf_sched {int /*<<< orphan*/  work_done_wait_mutex; int /*<<< orphan*/  start_work_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 int /*<<< orphan*/  PR_SET_NAME ; 
 int /*<<< orphan*/  free (struct sched_thread_parms*) ; 
 scalar_t__ get_cpu_usage_nsec_self (int) ; 
 int /*<<< orphan*/  perf_sched__process_event (struct perf_sched*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,char*) ; 
 unsigned long pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 unsigned long pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int self_open_counters () ; 
 unsigned long sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void *thread_func(void *ctx)
{
	struct sched_thread_parms *parms = ctx;
	struct task_desc *this_task = parms->task;
	struct perf_sched *sched = parms->sched;
	u64 cpu_usage_0, cpu_usage_1;
	unsigned long i, ret;
	char comm2[22];
	int fd;

	free(parms);

	sprintf(comm2, ":%s", this_task->comm);
	prctl(PR_SET_NAME, comm2);
	fd = self_open_counters();
	if (fd < 0)
		return NULL;
again:
	ret = sem_post(&this_task->ready_for_work);
	BUG_ON(ret);
	ret = pthread_mutex_lock(&sched->start_work_mutex);
	BUG_ON(ret);
	ret = pthread_mutex_unlock(&sched->start_work_mutex);
	BUG_ON(ret);

	cpu_usage_0 = get_cpu_usage_nsec_self(fd);

	for (i = 0; i < this_task->nr_events; i++) {
		this_task->curr_event = i;
		perf_sched__process_event(sched, this_task->atoms[i]);
	}

	cpu_usage_1 = get_cpu_usage_nsec_self(fd);
	this_task->cpu_usage = cpu_usage_1 - cpu_usage_0;
	ret = sem_post(&this_task->work_done_sem);
	BUG_ON(ret);

	ret = pthread_mutex_lock(&sched->work_done_wait_mutex);
	BUG_ON(ret);
	ret = pthread_mutex_unlock(&sched->work_done_wait_mutex);
	BUG_ON(ret);

	goto again;
}