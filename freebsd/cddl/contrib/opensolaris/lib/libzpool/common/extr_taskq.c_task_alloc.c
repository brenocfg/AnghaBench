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
struct TYPE_6__ {scalar_t__ tq_nalloc; scalar_t__ tq_minalloc; scalar_t__ tq_maxalloc; int /*<<< orphan*/  tq_lock; int /*<<< orphan*/  tq_maxalloc_wait; int /*<<< orphan*/  tq_maxalloc_cv; TYPE_2__* tq_freelist; } ;
typedef  TYPE_1__ taskq_t ;
struct TYPE_7__ {struct TYPE_7__* tqent_next; } ;
typedef  TYPE_2__ taskq_ent_t ;

/* Variables and functions */
 int KM_SLEEP ; 
 int cv_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ddi_get_lbolt () ; 
 scalar_t__ hz ; 
 TYPE_2__* kmem_alloc (int,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static taskq_ent_t *
task_alloc(taskq_t *tq, int tqflags)
{
	taskq_ent_t *t;
	int rv;

again:	if ((t = tq->tq_freelist) != NULL && tq->tq_nalloc >= tq->tq_minalloc) {
		tq->tq_freelist = t->tqent_next;
	} else {
		if (tq->tq_nalloc >= tq->tq_maxalloc) {
			if (!(tqflags & KM_SLEEP))
				return (NULL);

			/*
			 * We don't want to exceed tq_maxalloc, but we can't
			 * wait for other tasks to complete (and thus free up
			 * task structures) without risking deadlock with
			 * the caller.  So, we just delay for one second
			 * to throttle the allocation rate. If we have tasks
			 * complete before one second timeout expires then
			 * taskq_ent_free will signal us and we will
			 * immediately retry the allocation.
			 */
			tq->tq_maxalloc_wait++;
#ifdef __FreeBSD__
			rv = cv_timedwait(&tq->tq_maxalloc_cv,
			    &tq->tq_lock, hz);
#else
			rv = cv_timedwait(&tq->tq_maxalloc_cv,
			    &tq->tq_lock, ddi_get_lbolt() + hz);
#endif
			tq->tq_maxalloc_wait--;
			if (rv > 0)
				goto again;		/* signaled */
		}
		mutex_exit(&tq->tq_lock);

		t = kmem_alloc(sizeof (taskq_ent_t), tqflags & KM_SLEEP);

		mutex_enter(&tq->tq_lock);
		if (t != NULL)
			tq->tq_nalloc++;
	}
	return (t);
}