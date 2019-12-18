#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int tx_bytes; } ;
struct net_device {int /*<<< orphan*/  trans_start; TYPE_1__ stats; scalar_t__ mem_start; } ;
struct lance_regs {int /*<<< orphan*/  rdp; } ;
struct lance_private {int tx_new; int* tx_buf_ptr_lnc; int /*<<< orphan*/  lock; int /*<<< orphan*/  type; scalar_t__* tx_buf_ptr_cpu; struct lance_regs* ll; } ;
struct TYPE_4__ {int /*<<< orphan*/  tmd1; int /*<<< orphan*/  misc; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int ETH_ZLEN ; 
 int LE_C0_INEA ; 
 int LE_C0_TDMD ; 
 int LE_T1_OWN ; 
 int LE_T1_POK ; 
 int NETDEV_TX_OK ; 
 scalar_t__ TX_BUFFS_AVAIL ; 
 int TX_RING_MOD_MASK ; 
 TYPE_2__* btx_ring ; 
 int /*<<< orphan*/  cp_to_buf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int* lib_ptr (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_padto (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lance_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_regs *ll = lp->ll;
	volatile u16 *ib = (volatile u16 *)dev->mem_start;
	unsigned long flags;
	int entry, len;

	len = skb->len;

	if (len < ETH_ZLEN) {
		if (skb_padto(skb, ETH_ZLEN))
			return NETDEV_TX_OK;
		len = ETH_ZLEN;
	}

	dev->stats.tx_bytes += len;

	spin_lock_irqsave(&lp->lock, flags);

	entry = lp->tx_new;
	*lib_ptr(ib, btx_ring[entry].length, lp->type) = (-len);
	*lib_ptr(ib, btx_ring[entry].misc, lp->type) = 0;

	cp_to_buf(lp->type, (char *)lp->tx_buf_ptr_cpu[entry], skb->data, len);

	/* Now, give the packet to the lance */
	*lib_ptr(ib, btx_ring[entry].tmd1, lp->type) =
		((lp->tx_buf_ptr_lnc[entry] >> 16) & 0xff) |
		(LE_T1_POK | LE_T1_OWN);
	lp->tx_new = (entry + 1) & TX_RING_MOD_MASK;

	if (TX_BUFFS_AVAIL <= 0)
		netif_stop_queue(dev);

	/* Kick the lance: transmit now */
	writereg(&ll->rdp, LE_C0_INEA | LE_C0_TDMD);

	spin_unlock_irqrestore(&lp->lock, flags);

	dev->trans_start = jiffies;
	dev_kfree_skb(skb);

 	return NETDEV_TX_OK;
}