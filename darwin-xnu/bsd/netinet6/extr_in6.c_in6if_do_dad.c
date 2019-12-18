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
struct nd_ifinfo {scalar_t__ initialized; int flags; } ;
struct ifnet {int if_flags; int if_eflags; scalar_t__ if_subfamily; int if_type; } ;

/* Variables and functions */
 int IFEF_DIRECTLINK ; 
 int IFEF_IPV6_ND6ALT ; 
 int IFEF_LOCALNET_PRIVATE ; 
 int IFF_LOOPBACK ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 scalar_t__ IFNET_SUBFAMILY_IPSEC ; 
 scalar_t__ IFNET_SUBFAMILY_UTUN ; 
#define  IFT_DUMMY 129 
#define  IFT_FAITH 128 
 int ND6_IFF_DAD ; 
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 

int
in6if_do_dad(
	struct ifnet *ifp)
{
	struct nd_ifinfo *ndi = NULL;

	if ((ifp->if_flags & IFF_LOOPBACK) != 0)
		return (0);

	ndi = ND_IFINFO(ifp);
	VERIFY((NULL != ndi)  && (TRUE == ndi->initialized));
	if (!(ndi->flags & ND6_IFF_DAD))
		return (0);

	/*
	 * If we are using the alternative neighbor discovery
	 * interface on this interface, then skip DAD.
	 *
	 * Also, skip it for interfaces marked "local private"
	 * for now, even when not marked as using the alternative
	 * interface.  This is for historical reasons.
	 */
	if (ifp->if_eflags & 
	    (IFEF_IPV6_ND6ALT|IFEF_LOCALNET_PRIVATE|IFEF_DIRECTLINK))
		return (0);

	if (ifp->if_subfamily == IFNET_SUBFAMILY_IPSEC ||
		ifp->if_subfamily == IFNET_SUBFAMILY_UTUN) {
		/*
		 * Ignore DAD for tunneling virtual interfaces, which get
		 * their IPv6 address explicitly assigned.
		 */
		return (0);
	}

	switch (ifp->if_type) {
#if IFT_DUMMY
	case IFT_DUMMY:
#endif
	case IFT_FAITH:
		/*
		 * These interfaces do not have the IFF_LOOPBACK flag,
		 * but loop packets back.  We do not have to do DAD on such
		 * interfaces.  We should even omit it, because loop-backed
		 * NS would confuse the DAD procedure.
		 */
		return (0);
	default:
		/*
		 * Our DAD routine requires the interface up and running.
		 * However, some interfaces can be up before the RUNNING
		 * status.  Additionaly, users may try to assign addresses
		 * before the interface becomes up (or running).
		 * We simply skip DAD in such a case as a work around.
		 * XXX: we should rather mark "tentative" on such addresses,
		 * and do DAD after the interface becomes ready.
		 */
		if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) !=
		    (IFF_UP|IFF_RUNNING))
			return (0);

		return (1);
	}
}