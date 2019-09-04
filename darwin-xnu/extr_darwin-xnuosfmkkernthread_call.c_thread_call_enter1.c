#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_call_t ;
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  TYPE_3__* thread_call_group_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  pending_queue; } ;
struct TYPE_9__ {int /*<<< orphan*/  param1; int /*<<< orphan*/ * queue; int /*<<< orphan*/ * func; } ;
struct TYPE_10__ {int tc_flags; TYPE_1__ tc_call; } ;

/* Variables and functions */
 int THREAD_CALL_SIGNAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _pending_call_enqueue (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disable_ints_and_lock () ; 
 int /*<<< orphan*/  enable_ints_and_unlock (int /*<<< orphan*/ ) ; 
 TYPE_3__* thread_call_get_group (TYPE_2__*) ; 

boolean_t
thread_call_enter1(
		thread_call_t			call,
		thread_call_param_t		param1)
{
	boolean_t		result = TRUE;
	thread_call_group_t	group;

	assert(call->tc_call.func != NULL);

	assert((call->tc_flags & THREAD_CALL_SIGNAL) == 0);

	group = thread_call_get_group(call);

	spl_t s = disable_ints_and_lock();

	if (call->tc_call.queue != &group->pending_queue) {
		result = _pending_call_enqueue(call, group);
	}

	call->tc_call.param1 = param1;

	enable_ints_and_unlock(s);

	return (result);
}