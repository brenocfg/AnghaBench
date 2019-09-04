#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_call_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/ * queue; } ;
struct TYPE_7__ {int tc_flags; scalar_t__ tc_refs; scalar_t__ tc_finish_count; scalar_t__ tc_submit_count; TYPE_1__ tc_call; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int THREAD_CALL_RESCHEDULE ; 
 int THREAD_CALL_RUNNING ; 
 int THREAD_CALL_SIGNAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disable_ints_and_lock () ; 
 int /*<<< orphan*/  enable_ints_and_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_unlock () ; 
 int /*<<< orphan*/  thread_call_wait_once_locked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

boolean_t
thread_call_free(
		thread_call_t		call)
{
	spl_t s = disable_ints_and_lock();

	if (call->tc_call.queue != NULL ||
	   ((call->tc_flags & THREAD_CALL_RESCHEDULE) != 0)) {
		thread_call_unlock();
		splx(s);

		return (FALSE);
	}

	int32_t refs = --call->tc_refs;
	if (refs < 0) {
		panic("Refcount negative: %d\n", refs);
	}

	if ((THREAD_CALL_SIGNAL | THREAD_CALL_RUNNING)
	  == ((THREAD_CALL_SIGNAL | THREAD_CALL_RUNNING) & call->tc_flags)) {
		thread_call_wait_once_locked(call, s);
		/* thread call lock has been unlocked */
	} else {
		enable_ints_and_unlock(s);
	}

	if (refs == 0) {
		assert(call->tc_finish_count == call->tc_submit_count);
		zfree(thread_call_zone, call);
	}

	return (TRUE);
}