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
struct inet6_ifaddr {int /*<<< orphan*/  addr; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct inet6_ifaddr* addr_list; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_set (struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bond_glean_dev_ipv6(struct net_device *dev, struct in6_addr *addr)
{
	struct inet6_dev *idev;
	struct inet6_ifaddr *ifa;

	if (!dev)
		return;

	idev = in6_dev_get(dev);
	if (!idev)
		return;

	read_lock_bh(&idev->lock);
	ifa = idev->addr_list;
	if (ifa)
		ipv6_addr_copy(addr, &ifa->addr);
	else
		ipv6_addr_set(addr, 0, 0, 0, 0);

	read_unlock_bh(&idev->lock);

	in6_dev_put(idev);
}