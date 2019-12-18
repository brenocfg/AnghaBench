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
typedef  int u32 ;
struct TYPE_3__ {int buff_stat; int len; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ tx_dma_t ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct net_device_stats {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; struct net_device_stats stats; } ;
struct au1000_private {size_t tx_head; int tx_full; TYPE_2__** tx_db_inuse; TYPE_1__** tx_dma_ring; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int dma_addr; scalar_t__ vaddr; } ;
typedef  TYPE_2__ db_dest_t ;

/* Variables and functions */
 int ETH_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int NUM_TX_DMA ; 
 int TX_DMA_ENABLE ; 
 int TX_T_DONE ; 
 int au1000_debug ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  update_tx_stats (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t au1000_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct au1000_private *aup = netdev_priv(dev);
	struct net_device_stats *ps = &dev->stats;
	volatile tx_dma_t *ptxd;
	u32 buff_stat;
	db_dest_t *pDB;
	int i;

	if (au1000_debug > 5)
		printk("%s: tx: aup %x len=%d, data=%p, head %d\n",
				dev->name, (unsigned)aup, skb->len,
				skb->data, aup->tx_head);

	ptxd = aup->tx_dma_ring[aup->tx_head];
	buff_stat = ptxd->buff_stat;
	if (buff_stat & TX_DMA_ENABLE) {
		/* We've wrapped around and the transmitter is still busy */
		netif_stop_queue(dev);
		aup->tx_full = 1;
		return NETDEV_TX_BUSY;
	}
	else if (buff_stat & TX_T_DONE) {
		update_tx_stats(dev, ptxd->status);
		ptxd->len = 0;
	}

	if (aup->tx_full) {
		aup->tx_full = 0;
		netif_wake_queue(dev);
	}

	pDB = aup->tx_db_inuse[aup->tx_head];
	skb_copy_from_linear_data(skb, pDB->vaddr, skb->len);
	if (skb->len < ETH_ZLEN) {
		for (i=skb->len; i<ETH_ZLEN; i++) {
			((char *)pDB->vaddr)[i] = 0;
		}
		ptxd->len = ETH_ZLEN;
	}
	else
		ptxd->len = skb->len;

	ps->tx_packets++;
	ps->tx_bytes += ptxd->len;

	ptxd->buff_stat = pDB->dma_addr | TX_DMA_ENABLE;
	au_sync();
	dev_kfree_skb(skb);
	aup->tx_head = (aup->tx_head + 1) & (NUM_TX_DMA - 1);
	dev->trans_start = jiffies;
	return NETDEV_TX_OK;
}