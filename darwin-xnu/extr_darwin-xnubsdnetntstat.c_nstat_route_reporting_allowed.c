#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct rtentry {struct ifnet* rt_ifp; } ;
struct ifnet {int dummy; } ;
struct TYPE_3__ {int npf_flags; } ;
typedef  TYPE_1__ nstat_provider_filter ;
typedef  scalar_t__ nstat_provider_cookie_t ;

/* Variables and functions */
 int NSTAT_FILTER_IFNET_FLAGS ; 
 int nstat_ifnet_to_flags (struct ifnet*) ; 

__attribute__((used)) static bool
nstat_route_reporting_allowed(nstat_provider_cookie_t cookie, nstat_provider_filter *filter)
{
	bool retval = true;

	if ((filter->npf_flags & NSTAT_FILTER_IFNET_FLAGS) != 0)
	{
		struct rtentry	*rt = (struct rtentry*)cookie;
		struct ifnet *ifp = rt->rt_ifp;

		if (ifp)
		{
			uint16_t interface_properties = nstat_ifnet_to_flags(ifp);

			if ((filter->npf_flags & interface_properties) == 0)
			{
				retval = false;
			}
		}
	}
	return retval;
}