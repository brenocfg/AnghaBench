#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  TYPE_1__* semaphore_t ;
typedef  TYPE_2__* ipc_port_t ;
struct TYPE_11__ {int /*<<< orphan*/  ip_srights; } ;
struct TYPE_10__ {scalar_t__ owner; scalar_t__ active; TYPE_2__* port; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ IP_VALID (TYPE_2__*) ; 
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_port_dealloc_kernel (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_pause (scalar_t__) ; 
 scalar_t__ os_ref_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  semaphore_destroy_internal (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  semaphore_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  semaphore_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  semaphore_zone ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ task_lock_try (scalar_t__) ; 
 int /*<<< orphan*/  task_unlock (scalar_t__) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
semaphore_dereference(
	semaphore_t		semaphore)
{
	uint32_t collisions;
	spl_t spl_level;

	if (semaphore == NULL)
		return;

	if (os_ref_release(&semaphore->ref_count) > 0) {
		return;
	}

	/*
	 * Last ref, clean up the port [if any]
	 * associated with the semaphore, destroy
	 * it (if still active) and then free
	 * the semaphore.
	 */
	ipc_port_t port = semaphore->port;

	if (IP_VALID(port)) {
		assert(!port->ip_srights);
		ipc_port_dealloc_kernel(port);
	}

	/*
	 * Lock the semaphore to lock in the owner task reference.
	 * Then continue to try to lock the task (inverse order).
	 */
	spl_level = splsched();
	semaphore_lock(semaphore);
	for (collisions = 0; semaphore->active; collisions++) {
		task_t task = semaphore->owner;

		assert(task != TASK_NULL);
		
		if (task_lock_try(task)) {
			semaphore_destroy_internal(task, semaphore);
			/* semaphore unlocked */
			splx(spl_level);
			task_unlock(task);
			goto out;
		}
		
		/* failed to get out-of-order locks */
		semaphore_unlock(semaphore);
		splx(spl_level);
		mutex_pause(collisions);
		spl_level = splsched();
		semaphore_lock(semaphore);
	}
	semaphore_unlock(semaphore);
	splx(spl_level);

 out:
	zfree(semaphore_zone, semaphore);
}