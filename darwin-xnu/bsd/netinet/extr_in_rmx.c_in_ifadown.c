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
struct radix_node_head {int /*<<< orphan*/  (* rnh_walktree ) (struct radix_node_head*,int /*<<< orphan*/ ,struct in_ifadown_arg*) ;} ;
struct in_ifadown_arg {int del; struct ifaddr* ifa; struct radix_node_head* rnh; } ;
struct ifaddr {int /*<<< orphan*/  ifa_flags; TYPE_1__* ifa_addr; } ;
struct TYPE_2__ {size_t sa_family; } ;

/* Variables and functions */
 size_t AF_INET ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_ROUTE ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  in_ifadownkill ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  routegenid_inet_update () ; 
 struct radix_node_head** rt_tables ; 
 int /*<<< orphan*/  stub1 (struct radix_node_head*,int /*<<< orphan*/ ,struct in_ifadown_arg*) ; 

int
in_ifadown(struct ifaddr *ifa, int delete)
{
	struct in_ifadown_arg arg;
	struct radix_node_head *rnh;

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);

	/*
	 * Holding rnh_lock here prevents the possibility of
	 * ifa from changing (e.g. in_ifinit), so it is safe
	 * to access its ifa_addr without locking.
	 */
	if (ifa->ifa_addr->sa_family != AF_INET)
		return (1);

	/* trigger route cache reevaluation */
	routegenid_inet_update();

	arg.rnh = rnh = rt_tables[AF_INET];
	arg.ifa = ifa;
	arg.del = delete;
	rnh->rnh_walktree(rnh, in_ifadownkill, &arg);
	IFA_LOCK_SPIN(ifa);
	ifa->ifa_flags &= ~IFA_ROUTE;
	IFA_UNLOCK(ifa);
	return (0);
}