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
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int __ipv6_dev_ac_dec (struct inet6_dev*,struct in6_addr*) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 

__attribute__((used)) static int ipv6_dev_ac_dec(struct net_device *dev, struct in6_addr *addr)
{
	int ret;
	struct inet6_dev *idev = in6_dev_get(dev);
	if (idev == NULL)
		return -ENODEV;
	ret = __ipv6_dev_ac_dec(idev, addr);
	in6_dev_put(idev);
	return ret;
}