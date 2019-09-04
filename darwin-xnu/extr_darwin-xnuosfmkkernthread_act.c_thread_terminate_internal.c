#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_11__ {int /*<<< orphan*/ * affinity_set; scalar_t__ started; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ KERN_TERMINATED ; 
 int /*<<< orphan*/  THREAD_INTERRUPTED ; 
 int /*<<< orphan*/  act_abort (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  thread_affinity_terminate (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_start (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_wait (TYPE_1__*,scalar_t__) ; 

kern_return_t
thread_terminate_internal(
	thread_t			thread)
{
	kern_return_t		result = KERN_SUCCESS;

	thread_mtx_lock(thread);

	if (thread->active) {
		thread->active = FALSE;

		act_abort(thread);

		if (thread->started)
			clear_wait(thread, THREAD_INTERRUPTED);
		else {
			thread_start(thread);
		}
	}
	else
		result = KERN_TERMINATED;

	if (thread->affinity_set != NULL)
		thread_affinity_terminate(thread);

	thread_mtx_unlock(thread);

	if (thread != current_thread() && result == KERN_SUCCESS)
		thread_wait(thread, FALSE);

	return (result);
}