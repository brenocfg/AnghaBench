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
struct net_device {int /*<<< orphan*/  tx_global_lock; int /*<<< orphan*/  rx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_for_each_tx_queue (struct net_device*,int /*<<< orphan*/  (*) (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_init_one_queue (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netdev_init_queues(struct net_device *dev)
{
	netdev_init_one_queue(dev, &dev->rx_queue, NULL);
	netdev_for_each_tx_queue(dev, netdev_init_one_queue, NULL);
	spin_lock_init(&dev->tx_global_lock);
}