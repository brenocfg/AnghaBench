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
struct net_device {int tx_queue_len; int /*<<< orphan*/  destructor; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev ; 
 int /*<<< orphan*/  irlan_eth_netdev_ops ; 

__attribute__((used)) static void irlan_eth_setup(struct net_device *dev)
{
	ether_setup(dev);

	dev->netdev_ops		= &irlan_eth_netdev_ops;
	dev->destructor		= free_netdev;


	/*
	 * Lets do all queueing in IrTTP instead of this device driver.
	 * Queueing here as well can introduce some strange latency
	 * problems, which we will avoid by setting the queue size to 0.
	 */
	/*
	 * The bugs in IrTTP and IrLAN that created this latency issue
	 * have now been fixed, and we can propagate flow control properly
	 * to the network layer. However, this requires a minimal queue of
	 * packets for the device.
	 * Without flow control, the Tx Queue is 14 (ttp) + 0 (dev) = 14
	 * With flow control, the Tx Queue is 7 (ttp) + 4 (dev) = 11
	 * See irlan_eth_flow_indication()...
	 * Note : this number was randomly selected and would need to
	 * be adjusted.
	 * Jean II */
	dev->tx_queue_len = 4;
}