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
struct net_device {int dummy; } ;
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  addrconf_add_lroute (struct net_device*) ; 
 int /*<<< orphan*/  addrconf_add_mroute (struct net_device*) ; 
 struct inet6_dev* ipv6_find_idev (struct net_device*) ; 

__attribute__((used)) static struct inet6_dev *addrconf_add_dev(struct net_device *dev)
{
	struct inet6_dev *idev;

	ASSERT_RTNL();

	if ((idev = ipv6_find_idev(dev)) == NULL)
		return NULL;

	/* Add default multicast route */
	addrconf_add_mroute(dev);

	/* Add link local route */
	addrconf_add_lroute(dev);
	return idev;
}