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
struct inet6_ifaddr {int /*<<< orphan*/  idev; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipv6_dev_ac_dec (int /*<<< orphan*/ ,struct in6_addr*) ; 
 scalar_t__ ipv6_addr_any (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_prefix (struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addrconf_leave_anycast(struct inet6_ifaddr *ifp)
{
	struct in6_addr addr;
	ipv6_addr_prefix(&addr, &ifp->addr, ifp->prefix_len);
	if (ipv6_addr_any(&addr))
		return;
	__ipv6_dev_ac_dec(ifp->idev, &addr);
}