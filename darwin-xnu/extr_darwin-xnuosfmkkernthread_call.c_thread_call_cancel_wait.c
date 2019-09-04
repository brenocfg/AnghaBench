#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* thread_call_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {TYPE_3__* thc_call; } ;
struct TYPE_12__ {TYPE_1__ thc_state; } ;
struct TYPE_10__ {int /*<<< orphan*/  func; } ;
struct TYPE_11__ {int tc_flags; TYPE_2__ tc_call; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int THREAD_CALL_ALLOC ; 
 int THREAD_CALL_ONCE ; 
 TYPE_8__* current_thread () ; 
 int /*<<< orphan*/  disable_ints_and_lock () ; 
 int /*<<< orphan*/  enable_ints_and_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ thread_call_cancel_locked (TYPE_3__*) ; 
 int /*<<< orphan*/  thread_call_wait_locked (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_wait_once_locked (TYPE_3__*,int /*<<< orphan*/ ) ; 

boolean_t
thread_call_cancel_wait(thread_call_t call)
{
	if ((call->tc_flags & THREAD_CALL_ALLOC) == 0)
		panic("thread_call_cancel_wait: can't wait on thread call whose storage I don't own");

	if (!ml_get_interrupts_enabled())
		panic("unsafe thread_call_cancel_wait");

	if (current_thread()->thc_state.thc_call == call)
		panic("thread_call_cancel_wait: deadlock waiting on self from inside call: %p to function %p",
		      call, call->tc_call.func);

	spl_t s = disable_ints_and_lock();

	boolean_t canceled = thread_call_cancel_locked(call);

	if ((call->tc_flags & THREAD_CALL_ONCE) == THREAD_CALL_ONCE) {
		/*
		 * A cancel-wait on a 'once' call will both cancel
		 * the pending call and wait for the in-flight call
		 */

		thread_call_wait_once_locked(call, s);
		/* thread call lock unlocked */
	} else {
		/*
		 * A cancel-wait on a normal call will only wait for the in-flight calls
		 * if it did not cancel the pending call.
		 *
		 * TODO: This seems less than useful - shouldn't it do the wait as well?
		 */

		if (canceled == FALSE) {
			thread_call_wait_locked(call, s);
			/* thread call lock unlocked */
		} else {
			enable_ints_and_unlock(s);
		}
	}

	return canceled;
}