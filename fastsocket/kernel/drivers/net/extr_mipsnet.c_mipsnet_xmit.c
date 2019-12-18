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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  mipsnet_put_todevice (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int mipsnet_xmit(struct sk_buff *skb, struct net_device *dev)
{
	/*
	 * Only one packet at a time. Once TXDONE interrupt is serviced, the
	 * queue will be restarted.
	 */
	netif_stop_queue(dev);
	mipsnet_put_todevice(dev, skb);

	return NETDEV_TX_OK;
}