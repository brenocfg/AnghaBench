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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct in_ifaddr {TYPE_1__* ifa_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ifa_list; struct net_device* dev; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib_add_ifaddr (struct in_ifaddr*) ; 
 int /*<<< orphan*/  fib_del_ifaddr (struct in_ifaddr*) ; 
 int /*<<< orphan*/  fib_disable_ip (struct net_device*,int) ; 
 int /*<<< orphan*/  fib_sync_up (struct net_device*) ; 
 int /*<<< orphan*/  rt_cache_flush (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fib_inetaddr_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct in_ifaddr *ifa = (struct in_ifaddr *)ptr;
	struct net_device *dev = ifa->ifa_dev->dev;

	switch (event) {
	case NETDEV_UP:
		fib_add_ifaddr(ifa);
#ifdef CONFIG_IP_ROUTE_MULTIPATH
		fib_sync_up(dev);
#endif
		rt_cache_flush(dev_net(dev), -1);
		break;
	case NETDEV_DOWN:
		fib_del_ifaddr(ifa);
		if (ifa->ifa_dev->ifa_list == NULL) {
			/* Last address was deleted from this interface.
			   Disable IP.
			 */
			fib_disable_ip(dev, 1);
		} else {
			rt_cache_flush(dev_net(dev), -1);
		}
		break;
	}
	return NOTIFY_DONE;
}