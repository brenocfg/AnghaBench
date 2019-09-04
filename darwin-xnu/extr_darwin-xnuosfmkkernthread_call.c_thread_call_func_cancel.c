#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  TYPE_1__* thread_call_group_t ;
typedef  int /*<<< orphan*/ * thread_call_func_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/ * delayed_queues; int /*<<< orphan*/  pending_queue; } ;

/* Variables and functions */
 size_t TCF_ABSOLUTE ; 
 size_t TCF_CONTINUOUS ; 
 size_t THREAD_CALL_INDEX_HIGH ; 
 int _cancel_func_from_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_ints_and_lock () ; 
 int /*<<< orphan*/  enable_ints_and_unlock (int /*<<< orphan*/ ) ; 
 TYPE_1__* thread_call_groups ; 

boolean_t
thread_call_func_cancel(
		thread_call_func_t		func,
		thread_call_param_t		param,
		boolean_t			cancel_all)
{
	boolean_t	result;

	assert(func != NULL);

	spl_t s = disable_ints_and_lock();

	/* Function-only thread calls are only kept in the default HIGH group */
	thread_call_group_t group = &thread_call_groups[THREAD_CALL_INDEX_HIGH];

	if (cancel_all) {
		/* exhaustively search every queue, and return true if any search found something */
		result = _cancel_func_from_queue(func, param, group, cancel_all, &group->pending_queue) |
		         _cancel_func_from_queue(func, param, group, cancel_all, &group->delayed_queues[TCF_ABSOLUTE])  |
		         _cancel_func_from_queue(func, param, group, cancel_all, &group->delayed_queues[TCF_CONTINUOUS]);
	} else {
		/* early-exit as soon as we find something, don't search other queues */
		result = _cancel_func_from_queue(func, param, group, cancel_all, &group->pending_queue) ||
		         _cancel_func_from_queue(func, param, group, cancel_all, &group->delayed_queues[TCF_ABSOLUTE]) ||
		         _cancel_func_from_queue(func, param, group, cancel_all, &group->delayed_queues[TCF_CONTINUOUS]);
	}

	enable_ints_and_unlock(s);

	return (result);
}