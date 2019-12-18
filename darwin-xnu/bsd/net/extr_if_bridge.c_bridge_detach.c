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
struct bridge_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_stp; } ;
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_cloner ; 
 scalar_t__ bridge_in_bsd_mode (struct bridge_softc*) ; 
 int /*<<< orphan*/  bridge_list_mtx ; 
 int /*<<< orphan*/  bridge_lock_grp ; 
 int /*<<< orphan*/  bridge_rtable_fini (struct bridge_softc*) ; 
 int /*<<< orphan*/  bstp_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_clone_softc_deallocate (int /*<<< orphan*/ *,struct bridge_softc*) ; 
 int /*<<< orphan*/  ifnet_release (int /*<<< orphan*/ ) ; 
 scalar_t__ ifnet_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_list ; 

__attribute__((used)) static void
bridge_detach(ifnet_t ifp)
{
	struct bridge_softc *sc = (struct bridge_softc *)ifnet_softc(ifp);

#if BRIDGESTP
	bstp_detach(&sc->sc_stp);
#endif /* BRIDGESTP */

	if (bridge_in_bsd_mode(sc)) {
		/* Tear down the routing table. */
		bridge_rtable_fini(sc);
	}

	lck_mtx_lock(&bridge_list_mtx);
	LIST_REMOVE(sc, sc_list);
	lck_mtx_unlock(&bridge_list_mtx);

	ifnet_release(ifp);

	lck_mtx_destroy(&sc->sc_mtx, bridge_lock_grp);
	if_clone_softc_deallocate(&bridge_cloner, sc);
}