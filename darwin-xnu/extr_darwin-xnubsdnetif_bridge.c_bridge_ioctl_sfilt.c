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
struct ifbrparam {int ifbrp_filter; } ;
struct bridge_softc {int sc_filter_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFBF_FILT_MASK ; 
 int IFBF_FILT_USEIPF ; 

__attribute__((used)) static int
bridge_ioctl_sfilt(struct bridge_softc *sc, void *arg)
{
	struct ifbrparam *param = arg;

	if (param->ifbrp_filter & ~IFBF_FILT_MASK)
		return (EINVAL);

#ifndef BRIDGE_IPF
	if (param->ifbrp_filter & IFBF_FILT_USEIPF)
		return (EINVAL);
#endif

	sc->sc_filter_flags = param->ifbrp_filter;

	return (0);
}