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
struct ifbrparam {int /*<<< orphan*/  ifbrp_cexceeded; } ;
struct bridge_softc {int /*<<< orphan*/  sc_brtexceeded; } ;

/* Variables and functions */

__attribute__((used)) static int
bridge_ioctl_grte(struct bridge_softc *sc, void *arg)
{
	struct ifbrparam *param = arg;

	param->ifbrp_cexceeded = sc->sc_brtexceeded;
	return (0);
}