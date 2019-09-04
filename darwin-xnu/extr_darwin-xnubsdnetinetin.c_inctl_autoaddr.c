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
struct ifreq {int /*<<< orphan*/  ifr_intval; } ;
struct ifnet {int if_eflags; } ;
typedef  int /*<<< orphan*/  intval ;

/* Variables and functions */
 int EBUSY ; 
 int IFEF_AUTOCONFIGURING ; 
 int IFEF_IPV4_ROUTER ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 

__attribute__((used)) static __attribute__((noinline)) int
inctl_autoaddr(struct ifnet *ifp, struct ifreq *ifr)
{
	int error = 0, intval;

	VERIFY(ifp != NULL);

	bcopy(&ifr->ifr_intval, &intval, sizeof (intval));

	ifnet_lock_exclusive(ifp);
	if (intval) {
		/*
		 * An interface in IPv4 router mode implies that it
		 * is configured with a static IP address and should
		 * not act as a DHCP client; prevent SIOCAUTOADDR from
		 * being set in that mode.
		 */
		if (ifp->if_eflags & IFEF_IPV4_ROUTER) {
			intval = 0;	/* be safe; clear flag if set */
			error = EBUSY;
		} else {
			ifp->if_eflags |= IFEF_AUTOCONFIGURING;
		}
	}
	if (!intval)
		ifp->if_eflags &= ~IFEF_AUTOCONFIGURING;
	ifnet_lock_done(ifp);

	return (error);
}