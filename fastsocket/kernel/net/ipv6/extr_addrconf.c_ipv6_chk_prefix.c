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
struct inet6_ifaddr {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; struct inet6_ifaddr* if_next; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct inet6_ifaddr* addr_list; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int ipv6_prefix_equal (struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

int ipv6_chk_prefix(struct in6_addr *addr, struct net_device *dev)
{
	struct inet6_dev *idev;
	struct inet6_ifaddr *ifa;
	int	onlink;

	onlink = 0;
	rcu_read_lock();
	idev = __in6_dev_get(dev);
	if (idev) {
		read_lock_bh(&idev->lock);
		for (ifa = idev->addr_list; ifa; ifa = ifa->if_next) {
			onlink = ipv6_prefix_equal(addr, &ifa->addr,
						   ifa->prefix_len);
			if (onlink)
				break;
		}
		read_unlock_bh(&idev->lock);
	}
	rcu_read_unlock();
	return onlink;
}