#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  thread_state_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {scalar_t__ inspection; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_ABORTED ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ KERN_TERMINATED ; 
 TYPE_1__* THREAD_NULL ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ machine_thread_get_state (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ machine_thread_state_convert_to_user (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_hold (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_release (TYPE_1__*) ; 
 scalar_t__ thread_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unstop (TYPE_1__*) ; 

__attribute__((used)) static inline kern_return_t
thread_get_state_internal(
	thread_t		thread,
	int						flavor,
	thread_state_t			state,			/* pointer to OUT array */
	mach_msg_type_number_t	*state_count,	/*IN/OUT*/
	boolean_t				to_user)
{
	kern_return_t		result = KERN_SUCCESS;

	if (thread == THREAD_NULL)
		return (KERN_INVALID_ARGUMENT);

	thread_mtx_lock(thread);

	if (thread->active) {
		if (thread != current_thread()) {
			thread_hold(thread);

			thread_mtx_unlock(thread);

			if (thread_stop(thread, FALSE)) {
				thread_mtx_lock(thread);
				result = machine_thread_get_state(
										thread, flavor, state, state_count);
				thread_unstop(thread);
			}
			else {
				thread_mtx_lock(thread);
				result = KERN_ABORTED;
			}

			thread_release(thread);
		}
		else
			result = machine_thread_get_state(
									thread, flavor, state, state_count);
	}
	else if (thread->inspection)
	{
		result = machine_thread_get_state(
									thread, flavor, state, state_count);
	}
	else
		result = KERN_TERMINATED;

	if (to_user && result == KERN_SUCCESS) {
		result = machine_thread_state_convert_to_user(thread, flavor, state,
				state_count);
	}

	thread_mtx_unlock(thread);

	return (result);
}