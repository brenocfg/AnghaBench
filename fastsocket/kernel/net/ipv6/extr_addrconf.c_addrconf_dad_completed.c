#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; } ;
struct inet6_ifaddr {int probes; int /*<<< orphan*/  lock; TYPE_2__* idev; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {scalar_t__ rtr_solicits; int /*<<< orphan*/  rtr_solicit_interval; } ;
struct TYPE_4__ {TYPE_1__ cnf; int /*<<< orphan*/  if_flags; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_RS ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IF_RS_SENT ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int /*<<< orphan*/  addrconf_mod_timer (struct inet6_ifaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_linklocal_allrouters ; 
 scalar_t__ ipv6_accept_ra (TYPE_2__*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_ifa_notify (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  ndisc_send_rs (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addrconf_dad_completed(struct inet6_ifaddr *ifp)
{
	struct net_device *	dev = ifp->idev->dev;

	/*
	 *	Configure the address for reception. Now it is valid.
	 */

	ipv6_ifa_notify(RTM_NEWADDR, ifp);

	/* If added prefix is link local and we are prepared to process
	   router advertisements, start sending router solicitations.
	 */

	if (ipv6_accept_ra(ifp->idev) &&
	    ifp->idev->cnf.rtr_solicits > 0 &&
	    (dev->flags&IFF_LOOPBACK) == 0 &&
	    (ipv6_addr_type(&ifp->addr) & IPV6_ADDR_LINKLOCAL)) {
		/*
		 *	If a host as already performed a random delay
		 *	[...] as part of DAD [...] there is no need
		 *	to delay again before sending the first RS
		 */
		ndisc_send_rs(ifp->idev->dev, &ifp->addr, &in6addr_linklocal_allrouters);

		spin_lock_bh(&ifp->lock);
		ifp->probes = 1;
		ifp->idev->if_flags |= IF_RS_SENT;
		addrconf_mod_timer(ifp, AC_RS, ifp->idev->cnf.rtr_solicit_interval);
		spin_unlock_bh(&ifp->lock);
	}
}