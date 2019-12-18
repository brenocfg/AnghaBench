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
struct inet6_dev {TYPE_1__* dev; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  __ipv6_dev_mc_dec (struct inet6_dev*,struct in6_addr*) ; 
 int /*<<< orphan*/  addrconf_addr_solict_mult (struct in6_addr*,struct in6_addr*) ; 

void addrconf_leave_solict(struct inet6_dev *idev, struct in6_addr *addr)
{
	struct in6_addr maddr;

	if (idev->dev->flags&(IFF_LOOPBACK|IFF_NOARP))
		return;

	addrconf_addr_solict_mult(addr, &maddr);
	__ipv6_dev_mc_dec(idev, &maddr);
}