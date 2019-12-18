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
struct TYPE_2__ {int /*<<< orphan*/  bdc_func; struct bridge_softc* bdc_sc; } ;
struct bridge_softc {int sc_flags; int sc_brtcnt; int sc_rthash_size; TYPE_1__ sc_resize_call; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 
 int SCF_DETACHING ; 
 int SCF_RESIZING ; 
 int bridge_rtable_hash_size_max ; 
 int /*<<< orphan*/  bridge_rthash_delayed_resize ; 
 int /*<<< orphan*/  bridge_schedule_delayed_call (TYPE_1__*) ; 

__attribute__((used)) static void
bridge_rthash_resize(struct bridge_softc *sc)
{
	BRIDGE_LOCK_ASSERT_HELD(sc);

	if ((sc->sc_flags & SCF_DETACHING) || (sc->sc_flags & SCF_RESIZING))
		return;

	/*
	 * Four entries per hash bucket is our ideal load factor
	 */
	if (sc->sc_brtcnt < sc->sc_rthash_size * 4)
		return;
	/*
	 * Hard limit on the size of the routing hash table
	 */
	if (sc->sc_rthash_size >= bridge_rtable_hash_size_max)
		return;

	sc->sc_resize_call.bdc_sc = sc;
	sc->sc_resize_call.bdc_func = bridge_rthash_delayed_resize;
	bridge_schedule_delayed_call(&sc->sc_resize_call);
}