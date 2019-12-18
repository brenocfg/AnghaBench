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
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  TYPE_1__* semaphore_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* SEMAPHORE_NULL ; 
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  semaphore_dereference (TYPE_1__*) ; 
 int /*<<< orphan*/  semaphore_destroy_internal (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  semaphore_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  semaphore_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (scalar_t__) ; 
 int /*<<< orphan*/  task_unlock (scalar_t__) ; 

kern_return_t
semaphore_destroy(
	task_t			task,
	semaphore_t		semaphore)
{
	spl_t spl_level;

	if (semaphore == SEMAPHORE_NULL)
		return KERN_INVALID_ARGUMENT;

	if (task == TASK_NULL) {
		semaphore_dereference(semaphore);
		return KERN_INVALID_ARGUMENT;
	}

	task_lock(task);
	spl_level = splsched();
	semaphore_lock(semaphore);

	if (semaphore->owner != task) {
		semaphore_unlock(semaphore);
		semaphore_dereference(semaphore);
		splx(spl_level);
		task_unlock(task);
		return KERN_INVALID_ARGUMENT;
	}

	semaphore_destroy_internal(task, semaphore);
	/* semaphore unlocked */

	splx(spl_level);
	task_unlock(task);

	semaphore_dereference(semaphore);
	return KERN_SUCCESS;
}