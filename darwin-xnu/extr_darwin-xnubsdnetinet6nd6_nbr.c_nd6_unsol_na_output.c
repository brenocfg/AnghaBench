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
struct in6_addr {int dummy; } ;
struct TYPE_2__ {struct in6_addr sin6_addr; } ;
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; TYPE_1__ ia_addr; } ;
struct ifnet {int if_flags; int if_eflags; } ;
struct ifaddr {struct ifnet* ifa_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_LOCK_SPIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 int IFEF_IPV6_ND6ALT ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  ND_NA_FLAG_OVERRIDE ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 scalar_t__ in6_setscope (struct in6_addr*,struct ifnet*,int /*<<< orphan*/ *) ; 
 struct in6_addr in6addr_linklocal_allnodes ; 
 int /*<<< orphan*/  nd6_na_output (struct ifnet*,struct in6_addr*,struct in6_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nd6_unsol_na_output(struct ifaddr *ifa)
{
	struct in6_ifaddr *ia = (struct in6_ifaddr *)ifa;
	struct ifnet *ifp = ifa->ifa_ifp;
	struct in6_addr saddr6, taddr6;

	if ((ifp->if_flags & IFF_UP) == 0 ||
	    (ifp->if_flags & IFF_RUNNING) == 0 ||
	    (ifp->if_eflags & IFEF_IPV6_ND6ALT) != 0)
		return;

	IFA_LOCK_SPIN(&ia->ia_ifa);
	taddr6 = ia->ia_addr.sin6_addr;
	IFA_UNLOCK(&ia->ia_ifa);
	if (in6_setscope(&taddr6, ifp, NULL) != 0)
		return;
	saddr6 = in6addr_linklocal_allnodes;
	if (in6_setscope(&saddr6, ifp, NULL) != 0)
		return;

	nd6log((LOG_INFO, "%s: sending unsolicited NA\n",
	    if_name(ifa->ifa_ifp)));

	nd6_na_output(ifp, &saddr6, &taddr6, ND_NA_FLAG_OVERRIDE, 1, NULL);
}