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
struct ifbrparam {int /*<<< orphan*/  ifbrp_maxage; } ;
struct bridge_softc {int /*<<< orphan*/  sc_stp; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bridge_in_bsd_mode (struct bridge_softc*) ; 
 int bstp_set_maxage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_ioctl_sma(struct bridge_softc *sc, void *arg)
{
#if BRIDGESTP
	struct ifbrparam *param = arg;

	if (!bridge_in_bsd_mode(sc)) {
		return (EOPNOTSUPP);
	}
	return (bstp_set_maxage(&sc->sc_stp, param->ifbrp_maxage));
#else /* !BRIDGESTP */
#pragma unused(sc, arg)
	return (EOPNOTSUPP);
#endif /* !BRIDGESTP */
}