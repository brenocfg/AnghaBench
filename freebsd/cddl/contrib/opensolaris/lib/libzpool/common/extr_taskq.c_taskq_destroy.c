#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct TYPE_8__ {int tq_nthreads; scalar_t__ tq_nalloc; int /*<<< orphan*/  tq_maxalloc_cv; int /*<<< orphan*/  tq_wait_cv; int /*<<< orphan*/  tq_dispatch_cv; int /*<<< orphan*/  tq_lock; int /*<<< orphan*/  tq_threadlock; struct TYPE_8__* tq_threadlist; int /*<<< orphan*/ * tq_freelist; scalar_t__ tq_minalloc; int /*<<< orphan*/  tq_flags; } ;
typedef  TYPE_1__ taskq_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  TASKQ_ACTIVE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_alloc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  thr_join (TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
taskq_destroy(taskq_t *tq)
{
	int t;
	int nthreads = tq->tq_nthreads;

	taskq_wait(tq);

	mutex_enter(&tq->tq_lock);

	tq->tq_flags &= ~TASKQ_ACTIVE;
	cv_broadcast(&tq->tq_dispatch_cv);

	while (tq->tq_nthreads != 0)
		cv_wait(&tq->tq_wait_cv, &tq->tq_lock);

	tq->tq_minalloc = 0;
	while (tq->tq_nalloc != 0) {
		ASSERT(tq->tq_freelist != NULL);
		task_free(tq, task_alloc(tq, KM_SLEEP));
	}

	mutex_exit(&tq->tq_lock);

	for (t = 0; t < nthreads; t++)
		(void) thr_join(tq->tq_threadlist[t], NULL, NULL);

	kmem_free(tq->tq_threadlist, nthreads * sizeof (thread_t));

	rw_destroy(&tq->tq_threadlock);
	mutex_destroy(&tq->tq_lock);
	cv_destroy(&tq->tq_dispatch_cv);
	cv_destroy(&tq->tq_wait_cv);
	cv_destroy(&tq->tq_maxalloc_cv);

	kmem_free(tq, sizeof (taskq_t));
}