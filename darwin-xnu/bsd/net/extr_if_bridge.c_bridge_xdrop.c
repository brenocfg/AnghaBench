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
struct bridge_softc {int /*<<< orphan*/  sc_iflist_xcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 

__attribute__((used)) static void
bridge_xdrop(struct bridge_softc *sc)
{
	BRIDGE_LOCK_ASSERT_HELD(sc);

	sc->sc_iflist_xcnt--;
}