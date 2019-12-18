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
struct inet6_ifaddr {int flags; int /*<<< orphan*/  probes; struct inet6_dev* idev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dad_transmits; scalar_t__ rtr_solicit_delay; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_DAD ; 
 int IFA_F_OPTIMISTIC ; 
 int /*<<< orphan*/  addrconf_mod_timer (struct inet6_ifaddr*,int /*<<< orphan*/ ,unsigned long) ; 
 int net_random () ; 

__attribute__((used)) static void addrconf_dad_kick(struct inet6_ifaddr *ifp)
{
	unsigned long rand_num;
	struct inet6_dev *idev = ifp->idev;

	if (ifp->flags & IFA_F_OPTIMISTIC)
		rand_num = 0;
	else
		rand_num = net_random() % (idev->cnf.rtr_solicit_delay ? : 1);

	ifp->probes = idev->cnf.dad_transmits;
	addrconf_mod_timer(ifp, AC_DAD, rand_num);
}