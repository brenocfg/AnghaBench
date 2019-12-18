#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; scalar_t__ mc_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_creg; } ;
typedef  TYPE_1__ rtl8150_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  async_set_registers (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void rtl8150_set_multicast(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	netif_stop_queue(netdev);
	if (netdev->flags & IFF_PROMISC) {
		dev->rx_creg |= cpu_to_le16(0x0001);
		dev_info(&netdev->dev, "%s: promiscuous mode\n", netdev->name);
	} else if (netdev->mc_count ||
		   (netdev->flags & IFF_ALLMULTI)) {
		dev->rx_creg &= cpu_to_le16(0xfffe);
		dev->rx_creg |= cpu_to_le16(0x0002);
		dev_info(&netdev->dev, "%s: allmulti set\n", netdev->name);
	} else {
		/* ~RX_MULTICAST, ~RX_PROMISCUOUS */
		dev->rx_creg &= cpu_to_le16(0x00fc);
	}
	async_set_registers(dev, RCR, 2);
	netif_wake_queue(netdev);
}