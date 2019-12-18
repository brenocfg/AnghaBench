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
typedef  int /*<<< orphan*/  uint8_t ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {struct in6_addr sin6_addr; } ;
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; TYPE_1__ ia_addr; } ;
struct ifnet {int if_flags; } ;
struct ifaddr {struct ifnet* ifa_ifp; } ;
struct dadq {int /*<<< orphan*/ * dad_nonce; int /*<<< orphan*/  dad_ns_ocount; int /*<<< orphan*/  dad_ns_tcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAD_LOCK (struct dadq*) ; 
 int /*<<< orphan*/  DAD_UNLOCK (struct dadq*) ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 int IFF_POINTOPOINT ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 int ND_OPT_NONCE_LEN32 ; 
 int /*<<< orphan*/  RandomULong () ; 
 scalar_t__ dad_enhanced ; 
 int /*<<< orphan*/  nd6_ns_output (struct ifnet*,int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nd6_dad_ns_output(struct dadq *dp, struct ifaddr *ifa)
{
	struct in6_ifaddr *ia = (struct in6_ifaddr *)ifa;
	struct ifnet *ifp = ifa->ifa_ifp;
	int i = 0;
	struct in6_addr taddr6;

	DAD_LOCK(dp);
	dp->dad_ns_tcount++;
	if ((ifp->if_flags & IFF_UP) == 0) {
		DAD_UNLOCK(dp);
		return;
	}
	if ((ifp->if_flags & IFF_RUNNING) == 0) {
		DAD_UNLOCK(dp);
		return;
	}

	dp->dad_ns_ocount++;
	DAD_UNLOCK(dp);
	IFA_LOCK_SPIN(&ia->ia_ifa);
	taddr6 = ia->ia_addr.sin6_addr;
	IFA_UNLOCK(&ia->ia_ifa);
	if (dad_enhanced != 0 && !(ifp->if_flags & IFF_POINTOPOINT)) {
		for (i = 0; i < ND_OPT_NONCE_LEN32; i++)
			dp->dad_nonce[i] = RandomULong();
		/*
		 * XXXHRS: Note that in the case that
		 * DupAddrDetectTransmits > 1, multiple NS messages with
		 * different nonces can be looped back in an unexpected
		 * order.  The current implementation recognizes only
		 * the latest nonce on the sender side.  Practically it
		 * should work well in almost all cases.
		 */
	}
	nd6_ns_output(ifp, NULL, &taddr6, NULL,
	    (uint8_t *)&dp->dad_nonce[0]);
}