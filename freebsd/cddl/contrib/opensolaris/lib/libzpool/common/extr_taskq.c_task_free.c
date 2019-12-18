#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tq_nalloc; scalar_t__ tq_minalloc; int /*<<< orphan*/  tq_maxalloc_cv; scalar_t__ tq_maxalloc_wait; int /*<<< orphan*/  tq_lock; TYPE_2__* tq_freelist; } ;
typedef  TYPE_1__ taskq_t ;
struct TYPE_7__ {struct TYPE_7__* tqent_next; } ;
typedef  TYPE_2__ taskq_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
task_free(taskq_t *tq, taskq_ent_t *t)
{
	if (tq->tq_nalloc <= tq->tq_minalloc) {
		t->tqent_next = tq->tq_freelist;
		tq->tq_freelist = t;
	} else {
		tq->tq_nalloc--;
		mutex_exit(&tq->tq_lock);
		kmem_free(t, sizeof (taskq_ent_t));
		mutex_enter(&tq->tq_lock);
	}

	if (tq->tq_maxalloc_wait)
		cv_signal(&tq->tq_maxalloc_cv);
}