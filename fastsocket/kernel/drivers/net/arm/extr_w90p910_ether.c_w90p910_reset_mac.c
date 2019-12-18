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
struct w90p910_ether {int cur_tx; int finish_tx; int cur_rx; } ;
struct net_device {void* trans_start; } ;

/* Variables and functions */
 void* jiffies ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_enable_cam (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_enable_cam_command (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_enable_mac_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_enable_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  w90p910_enable_tx (struct net_device*,int) ; 
 int /*<<< orphan*/  w90p910_init_desc (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_return_default_idle (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_set_curdest (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_set_fifo_threshold (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_trigger_rx (struct net_device*) ; 
 int /*<<< orphan*/  w90p910_trigger_tx (struct net_device*) ; 

__attribute__((used)) static void w90p910_reset_mac(struct net_device *dev)
{
	struct w90p910_ether *ether = netdev_priv(dev);

	w90p910_enable_tx(dev, 0);
	w90p910_enable_rx(dev, 0);
	w90p910_set_fifo_threshold(dev);
	w90p910_return_default_idle(dev);

	if (!netif_queue_stopped(dev))
		netif_stop_queue(dev);

	w90p910_init_desc(dev);

	dev->trans_start = jiffies;
	ether->cur_tx = 0x0;
	ether->finish_tx = 0x0;
	ether->cur_rx = 0x0;

	w90p910_set_curdest(dev);
	w90p910_enable_cam(dev);
	w90p910_enable_cam_command(dev);
	w90p910_enable_mac_interrupt(dev);
	w90p910_enable_tx(dev, 1);
	w90p910_enable_rx(dev, 1);
	w90p910_trigger_tx(dev);
	w90p910_trigger_rx(dev);

	dev->trans_start = jiffies;

	if (netif_queue_stopped(dev))
		netif_wake_queue(dev);
}