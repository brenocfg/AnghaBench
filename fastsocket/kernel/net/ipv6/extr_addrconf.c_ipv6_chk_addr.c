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
typedef  size_t u8 ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_ifaddr {int flags; int scope; TYPE_1__* idev; int /*<<< orphan*/  addr; struct inet6_ifaddr* lst_next; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int IFA_F_TENTATIVE ; 
 int IFA_HOST ; 
 int IFA_LINK ; 
 int /*<<< orphan*/  addrconf_hash_lock ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct inet6_ifaddr** inet6_addr_lst ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 
 size_t ipv6_addr_hash (struct in6_addr*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

int ipv6_chk_addr(struct net *net, struct in6_addr *addr,
		  struct net_device *dev, int strict)
{
	struct inet6_ifaddr * ifp;
	u8 hash = ipv6_addr_hash(addr);

	read_lock_bh(&addrconf_hash_lock);
	for(ifp = inet6_addr_lst[hash]; ifp; ifp=ifp->lst_next) {
		if (!net_eq(dev_net(ifp->idev->dev), net))
			continue;
		if (ipv6_addr_equal(&ifp->addr, addr) &&
		    !(ifp->flags&IFA_F_TENTATIVE)) {
			if (dev == NULL || ifp->idev->dev == dev ||
			    !(ifp->scope&(IFA_LINK|IFA_HOST) || strict))
				break;
		}
	}
	read_unlock_bh(&addrconf_hash_lock);
	return ifp != NULL;
}