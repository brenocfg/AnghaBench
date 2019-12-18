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
struct inet6_ifaddr {scalar_t__ scope; unsigned char flags; int /*<<< orphan*/  addr; struct inet6_ifaddr* if_next; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct inet6_ifaddr* addr_list; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 scalar_t__ IFA_LINK ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

int ipv6_get_lladdr(struct net_device *dev, struct in6_addr *addr,
		    unsigned char banned_flags)
{
	struct inet6_dev *idev;
	int err = -EADDRNOTAVAIL;

	rcu_read_lock();
	if ((idev = __in6_dev_get(dev)) != NULL) {
		struct inet6_ifaddr *ifp;

		read_lock_bh(&idev->lock);
		for (ifp=idev->addr_list; ifp; ifp=ifp->if_next) {
			if (ifp->scope == IFA_LINK && !(ifp->flags & banned_flags)) {
				ipv6_addr_copy(addr, &ifp->addr);
				err = 0;
				break;
			}
		}
		read_unlock_bh(&idev->lock);
	}
	rcu_read_unlock();
	return err;
}