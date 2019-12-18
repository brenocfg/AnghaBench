#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {void (* bdc_func ) (struct bridge_softc*) ;TYPE_1__ bdc_ts; struct bridge_softc* bdc_sc; } ;
struct bridge_softc {int sc_flags; TYPE_3__ sc_aging_timer; TYPE_2__* sc_ifp; } ;
struct TYPE_5__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 
 int IFF_RUNNING ; 
 int SCF_DETACHING ; 
 int /*<<< orphan*/  bridge_rtable_prune_period ; 
 int /*<<< orphan*/  bridge_rtage (struct bridge_softc*) ; 
 int /*<<< orphan*/  bridge_schedule_delayed_call (TYPE_3__*) ; 

__attribute__((used)) static void
bridge_aging_timer(struct bridge_softc *sc)
{
	BRIDGE_LOCK_ASSERT_HELD(sc);

	bridge_rtage(sc);

	if ((sc->sc_ifp->if_flags & IFF_RUNNING) &&
	    (sc->sc_flags & SCF_DETACHING) == 0) {
		sc->sc_aging_timer.bdc_sc = sc;
		sc->sc_aging_timer.bdc_func = bridge_aging_timer;
		sc->sc_aging_timer.bdc_ts.tv_sec = bridge_rtable_prune_period;
		bridge_schedule_delayed_call(&sc->sc_aging_timer);
	}
}