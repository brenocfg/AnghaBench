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
struct net {int dummy; } ;
struct inet6_ifaddr {unsigned int prefix_len; int /*<<< orphan*/  addr; struct inet6_ifaddr* if_next; } ;
struct inet6_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; struct inet6_ifaddr* addr_list; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  addrconf_ifdown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in6_ifa_hold (struct inet6_ifaddr*) ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_del_addr (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inet6_addr_del(struct net *net, int ifindex, struct in6_addr *pfx,
			  unsigned int plen)
{
	struct inet6_ifaddr *ifp;
	struct inet6_dev *idev;
	struct net_device *dev;

	if (plen > 128)
		return -EINVAL;

	dev = __dev_get_by_index(net, ifindex);
	if (!dev)
		return -ENODEV;

	if ((idev = __in6_dev_get(dev)) == NULL)
		return -ENXIO;

	read_lock_bh(&idev->lock);
	for (ifp = idev->addr_list; ifp; ifp=ifp->if_next) {
		if (ifp->prefix_len == plen &&
		    ipv6_addr_equal(pfx, &ifp->addr)) {
			in6_ifa_hold(ifp);
			read_unlock_bh(&idev->lock);

			ipv6_del_addr(ifp);

			/* If the last address is deleted administratively,
			   disable IPv6 on this interface.
			 */
			if (idev->addr_list == NULL)
				addrconf_ifdown(idev->dev, 1);
			return 0;
		}
	}
	read_unlock_bh(&idev->lock);
	return -EADDRNOTAVAIL;
}