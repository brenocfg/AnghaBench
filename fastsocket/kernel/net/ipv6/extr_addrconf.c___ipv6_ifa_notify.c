#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inet6_ifaddr {TYPE_3__* rt; int /*<<< orphan*/  addr; TYPE_5__* idev; } ;
struct TYPE_6__ {int /*<<< orphan*/  forwarding; } ;
struct TYPE_9__ {TYPE_1__ cnf; } ;
struct TYPE_7__ {int /*<<< orphan*/  dst; } ;
struct TYPE_8__ {TYPE_2__ u; int /*<<< orphan*/  rt6i_node; } ;

/* Variables and functions */
#define  RTM_DELADDR 129 
#define  RTM_NEWADDR 128 
 int /*<<< orphan*/  addrconf_join_anycast (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_leave_anycast (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_leave_solict (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet6_ifa_notify (int,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  ip6_del_rt (TYPE_3__*) ; 
 int /*<<< orphan*/  ip6_ins_rt (TYPE_3__*) ; 

__attribute__((used)) static void __ipv6_ifa_notify(int event, struct inet6_ifaddr *ifp)
{
	inet6_ifa_notify(event ? : RTM_NEWADDR, ifp);

	switch (event) {
	case RTM_NEWADDR:
		/*
		 * If the address was optimistic
		 * we inserted the route at the start of
		 * our DAD process, so we don't need
		 * to do it again
		 */
		if (!(ifp->rt->rt6i_node))
			ip6_ins_rt(ifp->rt);
		if (ifp->idev->cnf.forwarding)
			addrconf_join_anycast(ifp);
		break;
	case RTM_DELADDR:
		if (ifp->idev->cnf.forwarding)
			addrconf_leave_anycast(ifp);
		addrconf_leave_solict(ifp->idev, &ifp->addr);
		dst_hold(&ifp->rt->u.dst);
		if (ip6_del_rt(ifp->rt))
			dst_free(&ifp->rt->u.dst);
		break;
	}
}