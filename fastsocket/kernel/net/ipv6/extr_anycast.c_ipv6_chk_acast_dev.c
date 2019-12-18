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
struct inet6_dev {int /*<<< orphan*/  lock; struct ifacaddr6* ac_list; } ;
struct in6_addr {int dummy; } ;
struct ifacaddr6 {int /*<<< orphan*/  aca_addr; struct ifacaddr6* aca_next; } ;

/* Variables and functions */
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipv6_chk_acast_dev(struct net_device *dev, struct in6_addr *addr)
{
	struct inet6_dev *idev;
	struct ifacaddr6 *aca;

	idev = in6_dev_get(dev);
	if (idev) {
		read_lock_bh(&idev->lock);
		for (aca = idev->ac_list; aca; aca = aca->aca_next)
			if (ipv6_addr_equal(&aca->aca_addr, addr))
				break;
		read_unlock_bh(&idev->lock);
		in6_dev_put(idev);
		return aca != NULL;
	}
	return 0;
}