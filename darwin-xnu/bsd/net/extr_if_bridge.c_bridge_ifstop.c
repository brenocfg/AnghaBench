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
struct ifnet {struct bridge_softc* if_softc; } ;
struct bridge_softc {int /*<<< orphan*/  sc_stp; int /*<<< orphan*/  sc_aging_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 
 int /*<<< orphan*/  IFBF_FLUSHDYN ; 
 int IFF_RUNNING ; 
 int /*<<< orphan*/  bridge_cancel_delayed_call (int /*<<< orphan*/ *) ; 
 scalar_t__ bridge_in_bsd_mode (struct bridge_softc*) ; 
 int /*<<< orphan*/  bridge_rtflush (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_stop (int /*<<< orphan*/ *) ; 
 int ifnet_flags (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_set_flags (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bridge_ifstop(struct ifnet *ifp, int disable)
{
#pragma unused(disable)
	struct bridge_softc *sc = ifp->if_softc;

	BRIDGE_LOCK_ASSERT_HELD(sc);

	if ((ifnet_flags(ifp) & IFF_RUNNING) == 0)
		return;

	if (bridge_in_bsd_mode(sc)) {
		bridge_cancel_delayed_call(&sc->sc_aging_timer);

#if BRIDGESTP
		bstp_stop(&sc->sc_stp);
#endif /* BRIDGESTP */

		bridge_rtflush(sc, IFBF_FLUSHDYN);
	}
	(void) ifnet_set_flags(ifp, 0, IFF_RUNNING);
}