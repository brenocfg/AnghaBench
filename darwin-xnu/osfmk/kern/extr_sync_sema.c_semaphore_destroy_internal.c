#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  TYPE_2__* semaphore_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
struct TYPE_8__ {int active; int count; int /*<<< orphan*/  waitq; TYPE_1__* owner; } ;
struct TYPE_7__ {int /*<<< orphan*/  semaphores_owned; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SEMAPHORE_EVENT ; 
 TYPE_1__* TASK_NULL ; 
 int /*<<< orphan*/  THREAD_RESTART ; 
 int /*<<< orphan*/  WAITQ_ALL_PRIORITIES ; 
 int /*<<< orphan*/  WAITQ_UNLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  remqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semaphore_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  waitq_wakeup64_all_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
semaphore_destroy_internal(
	task_t			task,
	semaphore_t		semaphore)
{
	int			old_count;

	/* unlink semaphore from owning task */
	assert(semaphore->owner == task);
	remqueue((queue_entry_t) semaphore);
	semaphore->owner = TASK_NULL;
	task->semaphores_owned--;

	/*
	 *  Deactivate semaphore
	 */
	assert(semaphore->active);
	semaphore->active = FALSE;

	/*
	 *  Wakeup blocked threads  
	 */
	old_count = semaphore->count;
	semaphore->count = 0;

	if (old_count < 0) {
		waitq_wakeup64_all_locked(&semaphore->waitq,
					  SEMAPHORE_EVENT,
					  THREAD_RESTART, NULL,
					  WAITQ_ALL_PRIORITIES,
					  WAITQ_UNLOCK);
		/* waitq/semaphore is unlocked */
	} else {
		semaphore_unlock(semaphore);
	}
}