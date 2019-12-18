#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  TYPE_1__* aio_workq_t ;
struct TYPE_17__ {int flags; scalar_t__ procp; scalar_t__ uaiocbp; } ;
typedef  TYPE_2__ aio_workq_entry ;
struct TYPE_16__ {scalar_t__ aioq_count; int /*<<< orphan*/  aioq_waitq; int /*<<< orphan*/  aioq_entries; } ;
struct TYPE_15__ {int /*<<< orphan*/  aio_inflight_count; TYPE_1__* aio_async_workqs; } ;

/* Variables and functions */
 int AIO_FSYNC ; 
 int /*<<< orphan*/  AIO_fsync_delay ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAST_EVENT64_T (TYPE_1__*) ; 
 int /*<<< orphan*/  DBG_BSD_AIO ; 
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 TYPE_12__ aio_anchor ; 
 scalar_t__ aio_delay_fsync_request (TYPE_2__*) ; 
 int /*<<< orphan*/  aio_entry_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  aio_proc_lock_spin (scalar_t__) ; 
 int /*<<< orphan*/  aio_proc_unlock (scalar_t__) ; 
 scalar_t__ aio_work_thread ; 
 int /*<<< orphan*/  aio_workq_add_entry_locked (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  aio_workq_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  aio_workq_remove_entry_locked (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  aio_workq_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_assert_wait64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static aio_workq_entry *
aio_get_some_work( void )
{
	aio_workq_entry		 		*entryp = NULL;
	aio_workq_t 				queue = NULL;

	/* Just one queue for the moment.  In the future there will be many. */
	queue = &aio_anchor.aio_async_workqs[0];	
	aio_workq_lock_spin(queue);
	if (queue->aioq_count == 0) {
		goto nowork;
	}

	/* 
	 * Hold the queue lock.
	 *
	 * pop some work off the work queue and add to our active queue
	 * Always start with the queue lock held. 
	 */
	for(;;) {
		/* 
		 * Pull of of work queue.  Once it's off, it can't be cancelled,
		 * so we can take our ref once we drop the queue lock.
		 */
		entryp = TAILQ_FIRST(&queue->aioq_entries);

		/* 
		 * If there's no work or only fsyncs that need delay, go to sleep 
		 * and then start anew from aio_work_thread 
		 */
		if (entryp == NULL) {
			goto nowork;
		}

		aio_workq_remove_entry_locked(queue, entryp);
		
		aio_workq_unlock(queue);

		/* 
		 * Check if it's an fsync that must be delayed.  No need to lock the entry;
		 * that flag would have been set at initialization.
		 */
		if ( (entryp->flags & AIO_FSYNC) != 0 ) {
			/* 
			 * Check for unfinished operations on the same file
			 * in this proc's queue.
			 */
			aio_proc_lock_spin(entryp->procp);
			if ( aio_delay_fsync_request( entryp ) ) {
				/* It needs to be delayed.  Put it back on the end of the work queue */
				KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_fsync_delay)) | DBG_FUNC_NONE,
							  (int)entryp->procp, (int)entryp->uaiocbp, 0, 0, 0 );

				aio_proc_unlock(entryp->procp);

				aio_workq_lock_spin(queue);
				aio_workq_add_entry_locked(queue, entryp);
				continue;
			} 
			aio_proc_unlock(entryp->procp);
		}
		
		break;
	}

	aio_entry_ref(entryp);

	OSIncrementAtomic(&aio_anchor.aio_inflight_count);
	return( entryp );

nowork:
	/* We will wake up when someone enqueues something */
	waitq_assert_wait64(&queue->aioq_waitq, CAST_EVENT64_T(queue), THREAD_UNINT, 0);
	aio_workq_unlock(queue);
	thread_block( (thread_continue_t)aio_work_thread );

	// notreached
	return NULL;
}