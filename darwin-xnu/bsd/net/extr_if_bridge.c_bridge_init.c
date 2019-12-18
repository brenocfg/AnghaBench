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
struct ifnet {scalar_t__ if_softc; } ;
struct bridge_softc {int /*<<< orphan*/  sc_stp; } ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 
 int IFF_RUNNING ; 
 int /*<<< orphan*/  bridge_aging_timer (struct bridge_softc*) ; 
 scalar_t__ bridge_in_bsd_mode (struct bridge_softc*) ; 
 int /*<<< orphan*/  bstp_init (int /*<<< orphan*/ *) ; 
 int ifnet_flags (struct ifnet*) ; 
 scalar_t__ ifnet_set_flags (struct ifnet*,int,int) ; 

__attribute__((used)) static int
bridge_init(struct ifnet *ifp)
{
	struct bridge_softc *sc = (struct bridge_softc *)ifp->if_softc;
	errno_t error;

	BRIDGE_LOCK_ASSERT_HELD(sc);

	if ((ifnet_flags(ifp) & IFF_RUNNING))
		return (0);

	error = ifnet_set_flags(ifp, IFF_RUNNING, IFF_RUNNING);

	if (bridge_in_bsd_mode(sc)) {
		/*
		 * Calling bridge_aging_timer() is OK as there are no entries to
		 * age so we're just going to arm the timer
		 */
		bridge_aging_timer(sc);
#if BRIDGESTP
		if (error == 0)
			bstp_init(&sc->sc_stp);	/* Initialize Spanning Tree */
#endif /* BRIDGESTP */
	}
	return (error);
}