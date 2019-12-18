#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  TYPE_2__* semaphore_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_14__ {int count; int /*<<< orphan*/  waitq; int /*<<< orphan*/  active; } ;
struct TYPE_13__ {int wait_result; void (* sth_continuation ) (scalar_t__) ;TYPE_2__* sth_signalsemaphore; TYPE_2__* sth_waitsemaphore; } ;

/* Variables and functions */
 scalar_t__ KERN_ABORTED ; 
 scalar_t__ KERN_ALREADY_WAITING ; 
 scalar_t__ KERN_NOT_WAITING ; 
 scalar_t__ KERN_OPERATION_TIMED_OUT ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ KERN_TERMINATED ; 
 int /*<<< orphan*/  SEMAPHORE_EVENT ; 
 TYPE_2__* SEMAPHORE_NULL ; 
 int /*<<< orphan*/  SEMAPHORE_SIGNAL_PREPOST ; 
 int SEMAPHORE_TIMEOUT_NOBLOCK ; 
 int /*<<< orphan*/  THREAD_ABORTSAFE ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_INTERRUPTED ; 
 int /*<<< orphan*/  THREAD_NULL ; 
 int /*<<< orphan*/  TIMEOUT_NO_LEEWAY ; 
 int /*<<< orphan*/  TIMEOUT_URGENCY_USER_NORMAL ; 
 int /*<<< orphan*/  clear_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  kThreadWaitSemaphore ; 
 scalar_t__ semaphore_convert_wait_result (int) ; 
 int /*<<< orphan*/  semaphore_lock (TYPE_2__*) ; 
 scalar_t__ semaphore_signal_internal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semaphore_unlock (TYPE_2__*) ; 
 scalar_t__ semaphore_wait_continue ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_pending_block_hint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_assert_wait64_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static kern_return_t
semaphore_wait_internal(
	semaphore_t		wait_semaphore,
	semaphore_t		signal_semaphore,
	uint64_t		deadline,
	int				option,
	void 			(*caller_cont)(kern_return_t))
{
	int					wait_result;
	spl_t				spl_level;
	kern_return_t		kr = KERN_ALREADY_WAITING;

	spl_level = splsched();
	semaphore_lock(wait_semaphore);

	if (!wait_semaphore->active) {
		kr = KERN_TERMINATED;
	} else if (wait_semaphore->count > 0) {
		wait_semaphore->count--;
		kr = KERN_SUCCESS;
	} else if (option & SEMAPHORE_TIMEOUT_NOBLOCK) {
		kr = KERN_OPERATION_TIMED_OUT;
	} else {
		thread_t	self = current_thread();

		wait_semaphore->count = -1;  /* we don't keep an actual count */

		thread_set_pending_block_hint(self, kThreadWaitSemaphore);
		(void)waitq_assert_wait64_locked(
					&wait_semaphore->waitq,
					SEMAPHORE_EVENT,
					THREAD_ABORTSAFE,
					TIMEOUT_URGENCY_USER_NORMAL,
					deadline, TIMEOUT_NO_LEEWAY,
					self);
	}
	semaphore_unlock(wait_semaphore);
	splx(spl_level);

	/*
	 * wait_semaphore is unlocked so we are free to go ahead and
	 * signal the signal_semaphore (if one was provided).
	 */
	if (signal_semaphore != SEMAPHORE_NULL) {
		kern_return_t signal_kr;

		/*
		 * lock the signal semaphore reference we got and signal it.
		 * This will NOT block (we cannot block after having asserted
		 * our intention to wait above).
		 */
		signal_kr = semaphore_signal_internal(signal_semaphore,
						      THREAD_NULL,
						      SEMAPHORE_SIGNAL_PREPOST);

		if (signal_kr == KERN_NOT_WAITING)
			signal_kr = KERN_SUCCESS;
		else if (signal_kr == KERN_TERMINATED) {
			/* 
			 * Uh!Oh!  The semaphore we were to signal died.
			 * We have to get ourselves out of the wait in
			 * case we get stuck here forever (it is assumed
			 * that the semaphore we were posting is gating
			 * the decision by someone else to post the
			 * semaphore we are waiting on).  People will
			 * discover the other dead semaphore soon enough.
			 * If we got out of the wait cleanly (someone
			 * already posted a wakeup to us) then return that
			 * (most important) result.  Otherwise,
			 * return the KERN_TERMINATED status.
			 */
			thread_t self = current_thread();

			clear_wait(self, THREAD_INTERRUPTED);
			kr = semaphore_convert_wait_result(self->wait_result);
			if (kr == KERN_ABORTED)
				kr = KERN_TERMINATED;
		}
	}
	
	/*
	 * If we had an error, or we didn't really need to wait we can
	 * return now that we have signalled the signal semaphore.
	 */
	if (kr != KERN_ALREADY_WAITING)
		return kr;

	/*
	 * Now, we can block.  If the caller supplied a continuation
	 * pointer of his own for after the block, block with the
	 * appropriate semaphore continuation.  Thiswill gather the
	 * semaphore results, release references on the semaphore(s),
	 * and then call the caller's continuation.
	 */
	if (caller_cont) {
		thread_t self = current_thread();

		self->sth_continuation = caller_cont;
		self->sth_waitsemaphore = wait_semaphore;
		self->sth_signalsemaphore = signal_semaphore;
		wait_result = thread_block((thread_continue_t)semaphore_wait_continue);
	}
	else {
		wait_result = thread_block(THREAD_CONTINUE_NULL);
	}

	return (semaphore_convert_wait_result(wait_result));
}