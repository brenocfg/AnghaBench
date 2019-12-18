#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
struct lance_private {int tx_new; int tx_ring_mod_mask; int tx_full; int /*<<< orphan*/  devlock; struct lance_init_block* init_block; } ;
struct lance_init_block {TYPE_1__* btx_ring; int /*<<< orphan*/ ** tx_buf; } ;
struct TYPE_2__ {int length; int tmd1_bits; scalar_t__ misc; } ;

/* Variables and functions */
 int ETH_ZLEN ; 
 int LE_C0_INEA ; 
 int LE_C0_TDMD ; 
 int LE_T1_OWN ; 
 int LE_T1_POK ; 
 int NETDEV_TX_LOCKED ; 
 int NETDEV_TX_OK ; 
 scalar_t__ TX_BUFFS_AVAIL ; 
 int /*<<< orphan*/  WRITERDP (struct lance_private*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,void*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int lance_start_xmit (struct sk_buff *skb, struct net_device *dev)
{
        struct lance_private *lp = netdev_priv(dev);
        volatile struct lance_init_block *ib = lp->init_block;
        int entry, skblen, len;
        static int outs;
	unsigned long flags;

        if (!TX_BUFFS_AVAIL)
                return NETDEV_TX_LOCKED;

	netif_stop_queue (dev);

        skblen = skb->len;

#ifdef DEBUG_DRIVER
        /* dump the packet */
        {
                int i;

                for (i = 0; i < 64; i++) {
                        if ((i % 16) == 0)
                                printk ("\n");
                        printk ("%2.2x ", skb->data [i]);
                }
        }
#endif
        len = (skblen <= ETH_ZLEN) ? ETH_ZLEN : skblen;
        entry = lp->tx_new & lp->tx_ring_mod_mask;
        ib->btx_ring [entry].length = (-len) | 0xf000;
        ib->btx_ring [entry].misc = 0;

	if (skb->len < ETH_ZLEN)
		memset((void *)&ib->tx_buf[entry][0], 0, ETH_ZLEN);
        skb_copy_from_linear_data(skb, (void *)&ib->tx_buf[entry][0], skblen);

        /* Now, give the packet to the lance */
        ib->btx_ring [entry].tmd1_bits = (LE_T1_POK|LE_T1_OWN);
        lp->tx_new = (lp->tx_new+1) & lp->tx_ring_mod_mask;

        outs++;
        /* Kick the lance: transmit now */
        WRITERDP(lp, LE_C0_INEA | LE_C0_TDMD);
        dev->trans_start = jiffies;
        dev_kfree_skb (skb);

	spin_lock_irqsave (&lp->devlock, flags);
        if (TX_BUFFS_AVAIL)
		netif_start_queue (dev);
	else
		lp->tx_full = 1;
	spin_unlock_irqrestore (&lp->devlock, flags);

        return NETDEV_TX_OK;
}