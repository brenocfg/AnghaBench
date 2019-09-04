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
typedef  scalar_t__ u_int32_t ;
struct ifnet {struct bridge_softc* if_bridge; } ;
struct bridge_softc {int /*<<< orphan*/  sc_ifp; } ;
struct bridge_iflist {int /*<<< orphan*/  bif_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIFF_MEDIA_ACTIVE ; 
 int /*<<< orphan*/  BRIDGE_LOCK (struct bridge_softc*) ; 
 int /*<<< orphan*/  BRIDGE_UNLOCK (struct bridge_softc*) ; 
 int /*<<< orphan*/  bridge_link_event (int /*<<< orphan*/ ,scalar_t__) ; 
 struct bridge_iflist* bridge_lookup_member_if (struct bridge_softc*,struct ifnet*) ; 
 scalar_t__ bridge_updatelinkstatus (struct bridge_softc*) ; 
 scalar_t__ interface_media_active (struct ifnet*) ; 

__attribute__((used)) static void
bridge_iflinkevent(struct ifnet *ifp)
{
	struct bridge_softc *sc = ifp->if_bridge;
	struct bridge_iflist *bif;
	u_int32_t event_code = 0;

#if BRIDGE_DEBUG
	if (if_bridge_debug & BR_DBGF_LIFECYCLE)
		printf("%s: %s\n", __func__, ifp->if_xname);
#endif /* BRIDGE_DEBUG */

	/* Check if the interface is a bridge member */
	if (sc == NULL)
		return;

	BRIDGE_LOCK(sc);
	bif = bridge_lookup_member_if(sc, ifp);
	if (bif != NULL) {
		if (interface_media_active(ifp))
			bif->bif_flags |= BIFF_MEDIA_ACTIVE;
		else
			bif->bif_flags &= ~BIFF_MEDIA_ACTIVE;

			event_code = bridge_updatelinkstatus(sc);
	}
	BRIDGE_UNLOCK(sc);

	if (event_code != 0)
		bridge_link_event(sc->sc_ifp, event_code);
}