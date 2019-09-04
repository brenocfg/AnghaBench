#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  thread_call_func_t ;
struct bridge_softc {int sc_flags; } ;
struct TYPE_2__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct bridge_delayed_call {int bdc_flags; int /*<<< orphan*/ * bdc_thread_call; TYPE_1__ bdc_ts; struct bridge_softc* bdc_sc; } ;

/* Variables and functions */
 int BDCF_CANCELLING ; 
 int BDCF_OUTSTANDING ; 
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 
 int NSEC_PER_SEC ; 
 int SCF_DETACHING ; 
 scalar_t__ bridge_delayed_callback ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int,int*) ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (scalar_t__,int*) ; 
 int /*<<< orphan*/ * thread_call_allocate (int /*<<< orphan*/ ,struct bridge_delayed_call*) ; 
 int /*<<< orphan*/  thread_call_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_func_delayed (int /*<<< orphan*/ ,struct bridge_delayed_call*,int) ; 

__attribute__((used)) static void
bridge_schedule_delayed_call(struct bridge_delayed_call *call)
{
	uint64_t deadline = 0;
	struct bridge_softc *sc = call->bdc_sc;

	BRIDGE_LOCK_ASSERT_HELD(sc);

	if ((sc->sc_flags & SCF_DETACHING) ||
	    (call->bdc_flags & (BDCF_OUTSTANDING | BDCF_CANCELLING)))
		return;

	if (call->bdc_ts.tv_sec || call->bdc_ts.tv_nsec) {
		nanoseconds_to_absolutetime(
		    (uint64_t)call->bdc_ts.tv_sec * NSEC_PER_SEC +
		    call->bdc_ts.tv_nsec, &deadline);
		clock_absolutetime_interval_to_deadline(deadline, &deadline);
	}

	call->bdc_flags = BDCF_OUTSTANDING;

#if BRIDGE_DEBUG_DELAYED_CALLBACK
	if (if_bridge_debug & BR_DBGF_DELAYED_CALL)
		printf("%s: %s call 0x%llx flags 0x%x\n", __func__,
		    sc->sc_if_xname, (uint64_t)VM_KERNEL_ADDRPERM(call),
		    call->bdc_flags);
#endif /* BRIDGE_DEBUG_DELAYED_CALLBACK */

	if (call->bdc_ts.tv_sec || call->bdc_ts.tv_nsec)
		thread_call_func_delayed(
			(thread_call_func_t)bridge_delayed_callback,
			call, deadline);
	else {
		if (call->bdc_thread_call == NULL)
			call->bdc_thread_call = thread_call_allocate(
				(thread_call_func_t)bridge_delayed_callback,
				call);
		thread_call_enter(call->bdc_thread_call);
	}
}