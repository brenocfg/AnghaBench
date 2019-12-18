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
struct inet6_ifaddr {scalar_t__ probes; int flags; int /*<<< orphan*/  addr; struct inet6_dev* idev; int /*<<< orphan*/  lock; } ;
struct inet6_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; TYPE_1__* nd_parms; scalar_t__ dead; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  retrans_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_DAD ; 
 int IFA_F_DADFAILED ; 
 int IFA_F_OPTIMISTIC ; 
 int IFA_F_TENTATIVE ; 
 int /*<<< orphan*/  addrconf_addr_solict_mult (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  addrconf_dad_completed (struct inet6_ifaddr*) ; 
 scalar_t__ addrconf_dad_end (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_mod_timer (struct inet6_ifaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  ndisc_send_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addrconf_dad_timer(unsigned long data)
{
	struct inet6_ifaddr *ifp = (struct inet6_ifaddr *) data;
	struct inet6_dev *idev = ifp->idev;
	struct in6_addr mcaddr;

	if (!ifp->probes && addrconf_dad_end(ifp))
		goto out;

	read_lock_bh(&idev->lock);
	if (idev->dead) {
		read_unlock_bh(&idev->lock);
		goto out;
	}
	spin_lock_bh(&ifp->lock);
	if (ifp->probes == 0) {
		/*
		 * DAD was successful
		 */

		ifp->flags &= ~(IFA_F_TENTATIVE|IFA_F_OPTIMISTIC|IFA_F_DADFAILED);
		spin_unlock_bh(&ifp->lock);
		read_unlock_bh(&idev->lock);

		addrconf_dad_completed(ifp);

		goto out;
	}

	ifp->probes--;
	addrconf_mod_timer(ifp, AC_DAD, ifp->idev->nd_parms->retrans_time);
	spin_unlock_bh(&ifp->lock);
	read_unlock_bh(&idev->lock);

	/* send a neighbour solicitation for our addr */
	addrconf_addr_solict_mult(&ifp->addr, &mcaddr);
	ndisc_send_ns(ifp->idev->dev, NULL, &ifp->addr, &mcaddr, &in6addr_any);
out:
	in6_ifa_put(ifp);
}