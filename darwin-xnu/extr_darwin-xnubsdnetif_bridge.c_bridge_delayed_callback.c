#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bridge_softc {int sc_flags; } ;
struct bridge_delayed_call {int bdc_flags; int /*<<< orphan*/  (* bdc_func ) (struct bridge_softc*) ;struct bridge_softc* bdc_sc; } ;

/* Variables and functions */
 int BDCF_CANCELLING ; 
 int BDCF_OUTSTANDING ; 
 int /*<<< orphan*/  BRIDGE_LOCK (struct bridge_softc*) ; 
 int /*<<< orphan*/  BRIDGE_UNLOCK (struct bridge_softc*) ; 
 int SCF_DETACHING ; 
 int /*<<< orphan*/  stub1 (struct bridge_softc*) ; 
 int /*<<< orphan*/  wakeup (struct bridge_delayed_call*) ; 

__attribute__((used)) static void
bridge_delayed_callback(void *param)
{
	struct bridge_delayed_call *call = (struct bridge_delayed_call *)param;
	struct bridge_softc *sc = call->bdc_sc;

#if BRIDGE_DEBUG_DELAYED_CALLBACK
	if (bridge_delayed_callback_delay > 0) {
		struct timespec ts;

		ts.tv_sec = bridge_delayed_callback_delay;
		ts.tv_nsec = 0;

		printf("%s: sleeping for %d seconds\n",
		    __func__, bridge_delayed_callback_delay);

		msleep(&bridge_delayed_callback_delay, NULL, PZERO,
		    __func__, &ts);

		printf("%s: awoken\n", __func__);
	}
#endif /* BRIDGE_DEBUG_DELAYED_CALLBACK */

	BRIDGE_LOCK(sc);

#if BRIDGE_DEBUG_DELAYED_CALLBACK
	if (if_bridge_debug & BR_DBGF_DELAYED_CALL)
		printf("%s: %s call 0x%llx flags 0x%x\n", __func__,
		    sc->sc_if_xname, (uint64_t)VM_KERNEL_ADDRPERM(call),
		    call->bdc_flags);
#endif /* BRIDGE_DEBUG_DELAYED_CALLBACK */

	if (call->bdc_flags & BDCF_CANCELLING) {
		wakeup(call);
	} else {
		if ((sc->sc_flags & SCF_DETACHING) == 0)
			(*call->bdc_func)(sc);
		}
	call->bdc_flags &= ~BDCF_OUTSTANDING;
	BRIDGE_UNLOCK(sc);
}