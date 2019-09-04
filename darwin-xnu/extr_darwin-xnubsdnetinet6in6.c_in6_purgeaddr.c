#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in6_multi_mship {int dummy; } ;
struct TYPE_6__ {struct in6_multi_mship* lh_first; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {scalar_t__ sin6_family; } ;
struct in6_ifaddr {int ia_flags; int ia_plen; TYPE_3__ ia6_memberships; int /*<<< orphan*/  ia_ifa; TYPE_2__ ia_addr; TYPE_1__ ia_dstaddr; } ;
struct ifnet {int dummy; } ;
struct ifaddr {struct ifnet* ifa_ifp; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IFA_LOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int IFA_ROUTE ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  KEV_INET6_ADDR_DELETED ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct in6_multi_mship*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int RTF_HOST ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  i6mm_chain ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_notify_address (struct ifnet*,scalar_t__) ; 
 int /*<<< orphan*/  in6_ifremloop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_leavegroup (struct in6_multi_mship*) ; 
 int /*<<< orphan*/  in6_post_msg (struct ifnet*,int /*<<< orphan*/ ,struct in6_ifaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_unlink_ifa (struct in6_ifaddr*,struct ifnet*) ; 
 int /*<<< orphan*/  ip6_sprintf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nd6_dad_stop (struct ifaddr*) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int rtinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
in6_purgeaddr(struct ifaddr *ifa)
{
	struct ifnet *ifp = ifa->ifa_ifp;
	struct in6_ifaddr *ia = (struct in6_ifaddr *)ifa;
	struct in6_multi_mship *imm;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_NOTOWNED);

	/* stop DAD processing */
	nd6_dad_stop(ifa);

	/*
	 * delete route to the destination of the address being purged.
	 * The interface must be p2p or loopback in this case.
	 */
	IFA_LOCK(ifa);
	if ((ia->ia_flags & IFA_ROUTE) && ia->ia_plen == 128) {
		int error, rtf;

		IFA_UNLOCK(ifa);
		rtf = (ia->ia_dstaddr.sin6_family == AF_INET6) ? RTF_HOST : 0;
		error = rtinit(&(ia->ia_ifa), RTM_DELETE, rtf);
		if (error != 0) {
			log(LOG_ERR, "in6_purgeaddr: failed to remove "
			    "a route to the p2p destination: %s on %s, "
			    "errno=%d\n",
			    ip6_sprintf(&ia->ia_addr.sin6_addr), if_name(ifp),
			    error);
			/* proceed anyway... */
		}
		IFA_LOCK_SPIN(ifa);
		ia->ia_flags &= ~IFA_ROUTE;
	}
	IFA_UNLOCK(ifa);

	/* Remove ownaddr's loopback rtentry, if it exists. */
	in6_ifremloop(&(ia->ia_ifa));

	/*
	 * leave from multicast groups we have joined for the interface
	 */
	IFA_LOCK(ifa);
	while ((imm = ia->ia6_memberships.lh_first) != NULL) {
		LIST_REMOVE(imm, i6mm_chain);
		IFA_UNLOCK(ifa);
		in6_leavegroup(imm);
		IFA_LOCK(ifa);
	}
	IFA_UNLOCK(ifa);

	/* in6_unlink_ifa() will need exclusive access */
	in6_unlink_ifa(ia, ifp);
	in6_post_msg(ifp, KEV_INET6_ADDR_DELETED, ia, NULL);

	(void) ifnet_notify_address(ifp, AF_INET6);
}