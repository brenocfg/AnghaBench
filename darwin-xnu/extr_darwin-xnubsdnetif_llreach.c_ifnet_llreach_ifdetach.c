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
struct ifnet {int dummy; } ;

/* Variables and functions */

void
ifnet_llreach_ifdetach(struct ifnet *ifp)
{
#pragma unused(ifp)
	/*
	 * Nothing to do for now; the link-layer source tree might
	 * contain entries at this point, that are still referred
	 * to by route entries pointing to this ifp.
	 */
}