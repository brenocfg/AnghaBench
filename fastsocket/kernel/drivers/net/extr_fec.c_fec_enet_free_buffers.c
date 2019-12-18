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
struct net_device {int /*<<< orphan*/  dev; } ;
struct fec_enet_private {int /*<<< orphan*/ * tx_bounce; struct bufdesc* tx_bd_base; struct sk_buff** rx_skbuff; struct bufdesc* rx_bd_base; } ;
struct bufdesc {scalar_t__ cbd_bufaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  FEC_ENET_RX_FRSIZE ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fec_enet_free_buffers(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	int i;
	struct sk_buff *skb;
	struct bufdesc	*bdp;

	bdp = fep->rx_bd_base;
	for (i = 0; i < RX_RING_SIZE; i++) {
		skb = fep->rx_skbuff[i];

		if (bdp->cbd_bufaddr)
			dma_unmap_single(&dev->dev, bdp->cbd_bufaddr,
					FEC_ENET_RX_FRSIZE, DMA_FROM_DEVICE);
		if (skb)
			dev_kfree_skb(skb);
		bdp++;
	}

	bdp = fep->tx_bd_base;
	for (i = 0; i < TX_RING_SIZE; i++)
		kfree(fep->tx_bounce[i]);
}