#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ rtl8150_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8150_UNPLUG ; 
 int /*<<< orphan*/  disable_net_traffic (TYPE_1__*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_all_urbs (TYPE_1__*) ; 

__attribute__((used)) static int rtl8150_close(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	int res = 0;

	netif_stop_queue(netdev);
	if (!test_bit(RTL8150_UNPLUG, &dev->flags))
		disable_net_traffic(dev);
	unlink_all_urbs(dev);

	return res;
}