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
struct ifbrparam {int /*<<< orphan*/  ifbrp_csize; } ;
struct bridge_softc {int /*<<< orphan*/  sc_brtmax; } ;

/* Variables and functions */
 scalar_t__ bridge_in_bsd_mode (struct bridge_softc*) ; 
 int /*<<< orphan*/  bridge_rttrim (struct bridge_softc*) ; 

__attribute__((used)) static int
bridge_ioctl_scache(struct bridge_softc *sc, void *arg)
{
	struct ifbrparam *param = arg;

	sc->sc_brtmax = param->ifbrp_csize;
	if (bridge_in_bsd_mode(sc)) {
		bridge_rttrim(sc);
	}
	return (0);
}