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
struct cycx_x25_channel {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ WAN_CONNECTED ; 
 scalar_t__ WAN_CONNECTING ; 
 int /*<<< orphan*/  cycx_x25_chan_disconnect (struct net_device*) ; 
 struct cycx_x25_channel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int cycx_netdevice_stop(struct net_device *dev)
{
	struct cycx_x25_channel *chan = netdev_priv(dev);

	netif_stop_queue(dev);

	if (chan->state == WAN_CONNECTED || chan->state == WAN_CONNECTING)
		cycx_x25_chan_disconnect(dev);

	return 0;
}