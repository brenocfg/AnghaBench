#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ elp_device ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  check_3c505_dma (struct net_device*) ; 
 int elp_debug ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  prime_rx (struct net_device*) ; 
 int /*<<< orphan*/  send_packet (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t elp_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	unsigned long flags;
	elp_device *adapter = netdev_priv(dev);

	spin_lock_irqsave(&adapter->lock, flags);
	check_3c505_dma(dev);

	if (elp_debug >= 3)
		pr_debug("%s: request to send packet of length %d\n", dev->name, (int) skb->len);

	netif_stop_queue(dev);

	/*
	 * send the packet at skb->data for skb->len
	 */
	if (!send_packet(dev, skb)) {
		if (elp_debug >= 2) {
			pr_debug("%s: failed to transmit packet\n", dev->name);
		}
		spin_unlock_irqrestore(&adapter->lock, flags);
		return NETDEV_TX_BUSY;
	}
	if (elp_debug >= 3)
		pr_debug("%s: packet of length %d sent\n", dev->name, (int) skb->len);

	/*
	 * start the transmit timeout
	 */
	dev->trans_start = jiffies;

	prime_rx(dev);
	spin_unlock_irqrestore(&adapter->lock, flags);
	netif_start_queue(dev);
	return NETDEV_TX_OK;
}