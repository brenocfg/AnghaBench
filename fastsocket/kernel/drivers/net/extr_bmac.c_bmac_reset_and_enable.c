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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct bmac_data {int /*<<< orphan*/  lock; scalar_t__ sleeping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERMINPACKET ; 
 int /*<<< orphan*/  EnableNormal ; 
 int /*<<< orphan*/  INTDISABLE ; 
 int /*<<< orphan*/  bmac_enable_and_reset_chip (struct net_device*) ; 
 int /*<<< orphan*/  bmac_init_chip (struct net_device*) ; 
 int /*<<< orphan*/  bmac_init_rx_ring (struct bmac_data*) ; 
 int /*<<< orphan*/  bmac_init_tx_ring (struct bmac_data*) ; 
 int /*<<< orphan*/  bmac_start_chip (struct net_device*) ; 
 int /*<<< orphan*/  bmac_transmit_packet (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  bmwrite (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bmac_data* netdev_priv (struct net_device*) ; 
 unsigned char* skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bmac_reset_and_enable(struct net_device *dev)
{
	struct bmac_data *bp = netdev_priv(dev);
	unsigned long flags;
	struct sk_buff *skb;
	unsigned char *data;

	spin_lock_irqsave(&bp->lock, flags);
	bmac_enable_and_reset_chip(dev);
	bmac_init_tx_ring(bp);
	bmac_init_rx_ring(bp);
	bmac_init_chip(dev);
	bmac_start_chip(dev);
	bmwrite(dev, INTDISABLE, EnableNormal);
	bp->sleeping = 0;

	/*
	 * It seems that the bmac can't receive until it's transmitted
	 * a packet.  So we give it a dummy packet to transmit.
	 */
	skb = dev_alloc_skb(ETHERMINPACKET);
	if (skb != NULL) {
		data = skb_put(skb, ETHERMINPACKET);
		memset(data, 0, ETHERMINPACKET);
		memcpy(data, dev->dev_addr, 6);
		memcpy(data+6, dev->dev_addr, 6);
		bmac_transmit_packet(skb, dev);
	}
	spin_unlock_irqrestore(&bp->lock, flags);
}