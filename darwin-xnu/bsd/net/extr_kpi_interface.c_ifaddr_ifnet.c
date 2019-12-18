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
struct ifnet {int dummy; } ;
typedef  struct ifnet* ifnet_t ;
typedef  TYPE_1__* ifaddr_t ;
struct TYPE_3__ {struct ifnet* ifa_ifp; } ;

/* Variables and functions */

ifnet_t
ifaddr_ifnet(ifaddr_t ifa)
{
	struct ifnet *ifp;

	if (ifa == NULL)
		return (NULL);

	/* ifa_ifp is set once at creation time; it is never changed */
	ifp = ifa->ifa_ifp;

	return (ifp);
}