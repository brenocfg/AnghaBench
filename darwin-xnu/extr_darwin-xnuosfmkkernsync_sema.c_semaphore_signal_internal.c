#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  TYPE_1__* semaphore_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_5__ {int count; int /*<<< orphan*/  waitq; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 scalar_t__ KERN_NOT_WAITING ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ KERN_TERMINATED ; 
 int /*<<< orphan*/  SEMAPHORE_EVENT ; 
 int SEMAPHORE_SIGNAL_ALL ; 
 int SEMAPHORE_SIGNAL_PREPOST ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  WAITQ_ALL_PRIORITIES ; 
 int /*<<< orphan*/  WAITQ_KEEP_LOCKED ; 
 int /*<<< orphan*/  WAITQ_UNLOCK ; 
 int /*<<< orphan*/  semaphore_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  semaphore_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_wakeup64_all_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_wakeup64_one_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_wakeup64_thread_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
semaphore_signal_internal(
	semaphore_t		semaphore,
	thread_t		thread,
	int				options)
{
	kern_return_t kr;
	spl_t  spl_level;

	spl_level = splsched();
	semaphore_lock(semaphore);

	if (!semaphore->active) {
		semaphore_unlock(semaphore);
		splx(spl_level);
		return KERN_TERMINATED;
	}

	if (thread != THREAD_NULL) {
		if (semaphore->count < 0) {
			kr = waitq_wakeup64_thread_locked(
					&semaphore->waitq,
					SEMAPHORE_EVENT,
					thread,
					THREAD_AWAKENED,
					WAITQ_UNLOCK);
			/* waitq/semaphore is unlocked */
		} else {
			kr = KERN_NOT_WAITING;
			semaphore_unlock(semaphore);
		}
		splx(spl_level);
		return kr;
	} 

	if (options & SEMAPHORE_SIGNAL_ALL) {
		int old_count = semaphore->count;

		kr = KERN_NOT_WAITING;
		if (old_count < 0) {
			semaphore->count = 0;  /* always reset */
			kr = waitq_wakeup64_all_locked(
					&semaphore->waitq,
					SEMAPHORE_EVENT,
					THREAD_AWAKENED, NULL,
					WAITQ_ALL_PRIORITIES,
					WAITQ_UNLOCK);
			/* waitq / semaphore is unlocked */
		} else {
			if (options & SEMAPHORE_SIGNAL_PREPOST)
				semaphore->count++;
			kr = KERN_SUCCESS;
			semaphore_unlock(semaphore);
		}
		splx(spl_level);
		return kr;
	}
	
	if (semaphore->count < 0) {
		kr = waitq_wakeup64_one_locked(
					&semaphore->waitq,
					SEMAPHORE_EVENT,
					THREAD_AWAKENED, NULL,
					WAITQ_ALL_PRIORITIES,
					WAITQ_KEEP_LOCKED);
		if (kr == KERN_SUCCESS) {
			semaphore_unlock(semaphore);
			splx(spl_level);
			return KERN_SUCCESS;
		} else {
			semaphore->count = 0;  /* all waiters gone */
		}
	}

	if (options & SEMAPHORE_SIGNAL_PREPOST) {
		semaphore->count++;
	}

	semaphore_unlock(semaphore);
	splx(spl_level);
	return KERN_NOT_WAITING;
}