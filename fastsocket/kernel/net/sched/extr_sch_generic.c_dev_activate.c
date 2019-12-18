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
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/ * qdisc; } ;

/* Variables and functions */
 int /*<<< orphan*/  attach_default_qdiscs (struct net_device*) ; 
 int /*<<< orphan*/  dev_watchdog_up (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_for_each_tx_queue (struct net_device*,int /*<<< orphan*/  (*) (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),int*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  transition_one_qdisc (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dev_activate(struct net_device *dev)
{
	int need_watchdog;

	/* No queueing discipline is attached to device;
	   create default one i.e. pfifo_fast for devices,
	   which need queueing and noqueue_qdisc for
	   virtual interfaces
	 */

	if (dev->qdisc == &noop_qdisc)
		attach_default_qdiscs(dev);

	if (!netif_carrier_ok(dev))
		/* Delay activation until next carrier-on event */
		return;

	need_watchdog = 0;
	netdev_for_each_tx_queue(dev, transition_one_qdisc, &need_watchdog);
	transition_one_qdisc(dev, &dev->rx_queue, NULL);

	if (need_watchdog) {
		dev->trans_start = jiffies;
		dev_watchdog_up(dev);
	}
}