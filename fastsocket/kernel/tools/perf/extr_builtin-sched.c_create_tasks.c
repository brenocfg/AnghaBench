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
struct task_desc {int /*<<< orphan*/  thread; scalar_t__ curr_event; int /*<<< orphan*/  work_done_sem; int /*<<< orphan*/  ready_for_work; int /*<<< orphan*/  sleep_sem; } ;
struct sched_thread_parms {struct perf_sched* sched; struct task_desc* task; } ;
struct perf_sched {unsigned long nr_tasks; struct task_desc** tasks; int /*<<< orphan*/  work_done_wait_mutex; int /*<<< orphan*/  start_work_mutex; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PTHREAD_STACK_MIN ; 
 struct sched_thread_parms* malloc (int) ; 
 scalar_t__ max (int,int /*<<< orphan*/ ) ; 
 int pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setstacksize (int /*<<< orphan*/ *,size_t) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sched_thread_parms*) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_func ; 

__attribute__((used)) static void create_tasks(struct perf_sched *sched)
{
	struct task_desc *task;
	pthread_attr_t attr;
	unsigned long i;
	int err;

	err = pthread_attr_init(&attr);
	BUG_ON(err);
	err = pthread_attr_setstacksize(&attr,
			(size_t) max(16 * 1024, PTHREAD_STACK_MIN));
	BUG_ON(err);
	err = pthread_mutex_lock(&sched->start_work_mutex);
	BUG_ON(err);
	err = pthread_mutex_lock(&sched->work_done_wait_mutex);
	BUG_ON(err);
	for (i = 0; i < sched->nr_tasks; i++) {
		struct sched_thread_parms *parms = malloc(sizeof(*parms));
		BUG_ON(parms == NULL);
		parms->task = task = sched->tasks[i];
		parms->sched = sched;
		sem_init(&task->sleep_sem, 0, 0);
		sem_init(&task->ready_for_work, 0, 0);
		sem_init(&task->work_done_sem, 0, 0);
		task->curr_event = 0;
		err = pthread_create(&task->thread, &attr, thread_func, parms);
		BUG_ON(err);
	}
}