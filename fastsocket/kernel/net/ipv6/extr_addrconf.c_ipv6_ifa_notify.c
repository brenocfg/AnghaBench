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
struct inet6_ifaddr {TYPE_1__* idev; } ;
struct TYPE_2__ {scalar_t__ dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipv6_ifa_notify (int,struct inet6_ifaddr*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 

__attribute__((used)) static void ipv6_ifa_notify(int event, struct inet6_ifaddr *ifp)
{
	rcu_read_lock_bh();
	if (likely(ifp->idev->dead == 0))
		__ipv6_ifa_notify(event, ifp);
	rcu_read_unlock_bh();
}