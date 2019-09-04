#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  TYPE_2__* aio_workq_t ;
typedef  int /*<<< orphan*/  aio_workq_entry ;
struct TYPE_13__ {int /*<<< orphan*/  aioq_waitq; } ;
struct TYPE_12__ {int /*<<< orphan*/  p_aio_total_count; int /*<<< orphan*/  p_aio_active_count; int /*<<< orphan*/  p_aio_activeq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_AIO_PROC_LOCK_OWNED (TYPE_1__*) ; 
 int /*<<< orphan*/  CAST_EVENT64_T (TYPE_2__*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 int /*<<< orphan*/  WAITQ_ALL_PRIORITIES ; 
 TYPE_2__* aio_entry_workq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aio_proc_link ; 
 int /*<<< orphan*/  aio_proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  aio_proc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  aio_workq_add_entry_locked (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aio_workq_lock_spin (TYPE_2__*) ; 
 int /*<<< orphan*/  aio_workq_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  waitq_wakeup64_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aio_enqueue_work( proc_t procp, aio_workq_entry *entryp, int proc_locked)
{
#if 0
	aio_workq_entry	*my_entryp;	/* used for insertion sort */
#endif /* 0 */
	aio_workq_t queue = aio_entry_workq(entryp);

	if (proc_locked == 0) {
		aio_proc_lock(procp);
	}

	ASSERT_AIO_PROC_LOCK_OWNED(procp);

	/* Onto proc queue */
	TAILQ_INSERT_TAIL(&procp->p_aio_activeq, entryp,  aio_proc_link);
	procp->p_aio_active_count++;
	procp->p_aio_total_count++;

	/* And work queue */
	aio_workq_lock_spin(queue);
	aio_workq_add_entry_locked(queue, entryp);
	waitq_wakeup64_one(&queue->aioq_waitq, CAST_EVENT64_T(queue),
			   THREAD_AWAKENED, WAITQ_ALL_PRIORITIES);
	aio_workq_unlock(queue);
	
	if (proc_locked == 0) {
		aio_proc_unlock(procp);
	}

#if 0
	/*
	 * Procedure:
	 *
	 * (1)	The nice value is in the range PRIO_MIN..PRIO_MAX [-20..20]
	 * (2)	The normalized nice value is in the range 0..((2 * NZERO) - 1)
	 *	which is [0..39], with 0 not being used.  In nice values, the
	 *	lower the nice value, the higher the priority.
	 * (3)	The normalized scheduling prioritiy is the highest nice value
	 *	minus the current nice value.  In I/O scheduling priority, the
	 *	higher the value the lower the priority, so it is the inverse
	 *	of the nice value (the higher the number, the higher the I/O
	 *	priority).
	 * (4)	From the normalized scheduling priority, we subtract the
	 *	request priority to get the request priority value number;
	 *	this means that requests are only capable of depressing their
	 *	priority relative to other requests,
	 */
	entryp->priority = (((2 * NZERO) - 1) - procp->p_nice);

	/* only premit depressing the priority */
	if (entryp->aiocb.aio_reqprio < 0)
		entryp->aiocb.aio_reqprio = 0;
	if (entryp->aiocb.aio_reqprio > 0) {
		entryp->priority -= entryp->aiocb.aio_reqprio;
		if (entryp->priority < 0)
			entryp->priority = 0;
	}

	/* Insertion sort the entry; lowest ->priority to highest */
	TAILQ_FOREACH(my_entryp, &aio_anchor.aio_async_workq, aio_workq_link) {
		if ( entryp->priority <= my_entryp->priority) {
			TAILQ_INSERT_BEFORE(my_entryp, entryp, aio_workq_link);
			break;
		}
	}
	if (my_entryp == NULL)
		TAILQ_INSERT_TAIL( &aio_anchor.aio_async_workq, entryp, aio_workq_link );
#endif /* 0 */
}