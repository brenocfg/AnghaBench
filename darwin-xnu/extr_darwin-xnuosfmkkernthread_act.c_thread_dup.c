#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_15__ {scalar_t__ affinity_set; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ AFFINITY_SET_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_ABORTED ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KERN_TERMINATED ; 
 TYPE_1__* THREAD_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  machine_thread_dup (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_affinity_dup (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  thread_hold (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_release (TYPE_1__*) ; 
 scalar_t__ thread_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unstop (TYPE_1__*) ; 

kern_return_t
thread_dup(
	thread_t	target)
{
	thread_t			self = current_thread();
	kern_return_t		result = KERN_SUCCESS;

	if (target == THREAD_NULL || target == self)
		return (KERN_INVALID_ARGUMENT);

	thread_mtx_lock(target);

	if (target->active) {
		thread_hold(target);

		thread_mtx_unlock(target);

		if (thread_stop(target, TRUE)) {
			thread_mtx_lock(target);
			result = machine_thread_dup(self, target, FALSE);

			if (self->affinity_set != AFFINITY_SET_NULL)
				thread_affinity_dup(self, target);
			thread_unstop(target);
		}
		else {
			thread_mtx_lock(target);
			result = KERN_ABORTED;
		}

		thread_release(target);
	}
	else
		result = KERN_TERMINATED;

	thread_mtx_unlock(target);

	return (result);
}