#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* caddr_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_15__ {scalar_t__ sigev_notify; int /*<<< orphan*/  sigev_signo; } ;
struct TYPE_16__ {int /*<<< orphan*/  aio_fildes; TYPE_1__ aio_sigevent; } ;
struct TYPE_18__ {int flags; scalar_t__ uaiocbp; TYPE_8__* procp; TYPE_2__ aiocb; scalar_t__ group_tag; } ;
typedef  TYPE_4__ aio_workq_entry ;
struct TYPE_17__ {scalar_t__ io_completed; scalar_t__ io_issued; int io_waiter; } ;
typedef  TYPE_3__ aio_lio_context ;
struct TYPE_19__ {int /*<<< orphan*/  AIO_SUSPEND_SLEEP_CHAN; TYPE_3__ AIO_CLEANUP_SLEEP_CHAN; } ;

/* Variables and functions */
 int AIO_CLOSE_WAIT ; 
 int AIO_DISABLE ; 
 int AIO_EXIT_WAIT ; 
 int AIO_LIO_NOTIFY ; 
 int /*<<< orphan*/  AIO_completion_cleanup_wait ; 
 int /*<<< orphan*/  AIO_completion_cleanup_wake ; 
 int /*<<< orphan*/  AIO_completion_sig ; 
 int /*<<< orphan*/  AIO_completion_suspend_wake ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_BSD_AIO ; 
 int DBG_FUNC_NONE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SIGEV_SIGNAL ; 
 scalar_t__ TRUE ; 
 int aio_active_requests_for_process (TYPE_8__*) ; 
 int aio_proc_active_requests_for_file (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_proc_lock_spin (TYPE_8__*) ; 
 int /*<<< orphan*/  aio_proc_unlock (TYPE_8__*) ; 
 int /*<<< orphan*/  free_lio_context (TYPE_3__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  psignal (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (TYPE_3__*) ; 
 int /*<<< orphan*/  wakeup_one (TYPE_3__*) ; 

__attribute__((used)) static void
do_aio_completion( aio_workq_entry *entryp ) 
{

	boolean_t		lastLioCompleted = FALSE;
	aio_lio_context	*lio_context = NULL;
	int waiter = 0;
	
	lio_context = (aio_lio_context *)entryp->group_tag;
	
	if (lio_context != NULL) {
		
		aio_proc_lock_spin(entryp->procp);

		/* Account for this I/O completing. */
	 	lio_context->io_completed++;
		
		/* Are we done with this lio context? */
	 	if (lio_context->io_issued == lio_context->io_completed) {
	 		lastLioCompleted = TRUE;
	 	}
		
		waiter = lio_context->io_waiter;
		
		/* explicit wakeup of lio_listio() waiting in LIO_WAIT */
		if ((entryp->flags & AIO_LIO_NOTIFY) && (lastLioCompleted) && (waiter != 0)) {
			/* wake up the waiter */
			wakeup(lio_context);
		}
		
		aio_proc_unlock(entryp->procp);
	}
	
	if ( entryp->aiocb.aio_sigevent.sigev_notify == SIGEV_SIGNAL &&
		 (entryp->flags & AIO_DISABLE) == 0 ) {
		
		boolean_t	performSignal = FALSE;
		 if (lio_context == NULL) {
		 	performSignal = TRUE;
		 }
		 else {
			/* 
			 * If this was the last request in the group and a signal
			 * is desired, send one.
			 */
			performSignal = lastLioCompleted;
		 }
		 
		 if (performSignal) {
		 	
			KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_completion_sig)) | DBG_FUNC_NONE,
				 (int)entryp->procp, (int)entryp->uaiocbp, 
				 entryp->aiocb.aio_sigevent.sigev_signo, 0, 0 );
			
			psignal( entryp->procp, entryp->aiocb.aio_sigevent.sigev_signo );
		}
	}

	if ((entryp->flags & AIO_EXIT_WAIT) && (entryp->flags & AIO_CLOSE_WAIT)) {
		panic("Close and exit flags set at the same time\n");
	}
	
	/*
	 * need to handle case where a process is trying to exit, exec, or
	 * close and is currently waiting for active aio requests to complete.
	 * If AIO_CLEANUP_WAIT is set then we need to look to see if there are any 
	 * other requests in the active queue for this process.  If there are 
	 * none then wakeup using the AIO_CLEANUP_SLEEP_CHAN tsleep channel.
	 * If there are some still active then do nothing - we only want to
	 * wakeup when all active aio requests for the process are complete. 
	 *
	 * Don't need to lock the entry or proc to check the cleanup flag.  It can only be
	 * set for cancellation, while the entryp is still on a proc list; now it's 
	 * off, so that flag is already set if it's going to be.
	 */
	if ( (entryp->flags & AIO_EXIT_WAIT) != 0 ) {
		int		active_requests;

		KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_completion_cleanup_wait)) | DBG_FUNC_NONE,
					  (int)entryp->procp, (int)entryp->uaiocbp, 0, 0, 0 );
		
		aio_proc_lock_spin(entryp->procp);
		active_requests = aio_active_requests_for_process( entryp->procp );
		if ( active_requests < 1 ) {
			/* 
			 * no active aio requests for this process, continue exiting.  In this
			 * case, there should be no one else waiting ont he proc in AIO...
			 */
			wakeup_one((caddr_t)&entryp->procp->AIO_CLEANUP_SLEEP_CHAN);
			aio_proc_unlock(entryp->procp);

			KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_completion_cleanup_wake)) | DBG_FUNC_NONE,
					  	  (int)entryp->procp, (int)entryp->uaiocbp, 0, 0, 0 );
		} else {
			aio_proc_unlock(entryp->procp);
		}
	}
	
	if ( (entryp->flags & AIO_CLOSE_WAIT) != 0 ) {
		int		active_requests;

		KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_completion_cleanup_wait)) | DBG_FUNC_NONE,
					  (int)entryp->procp, (int)entryp->uaiocbp, 0, 0, 0 );
		
		aio_proc_lock_spin(entryp->procp);
		active_requests = aio_proc_active_requests_for_file( entryp->procp, entryp->aiocb.aio_fildes);
		if ( active_requests < 1 ) {
			/* Can't wakeup_one(); multiple closes might be in progress. */
			wakeup(&entryp->procp->AIO_CLEANUP_SLEEP_CHAN);
			aio_proc_unlock(entryp->procp);

			KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_completion_cleanup_wake)) | DBG_FUNC_NONE,
					  	  (int)entryp->procp, (int)entryp->uaiocbp, 0, 0, 0 );
		} else {
			aio_proc_unlock(entryp->procp);
		}
	}
	/* 
	 * A thread in aio_suspend() wants to known about completed IOs.  If it checked
	 * the done list before we moved our AIO there, then it already asserted its wait,
	 * and we can wake it up without holding the lock.  If it checked the list after
	 * we did our move, then it already has seen the AIO that we moved.  Herego, we
	 * can do our wakeup without holding the lock.
	 */
	wakeup( (caddr_t) &entryp->procp->AIO_SUSPEND_SLEEP_CHAN ); 
	KERNEL_DEBUG( (BSDDBG_CODE(DBG_BSD_AIO, AIO_completion_suspend_wake)) | DBG_FUNC_NONE,
				  (int)entryp->procp, (int)entryp->uaiocbp, 0, 0, 0 );

	/*   
	 * free the LIO context if the last lio completed and no thread is
	 * waiting
	 */
	if (lastLioCompleted && (waiter == 0)) 
		free_lio_context (lio_context);

	
}