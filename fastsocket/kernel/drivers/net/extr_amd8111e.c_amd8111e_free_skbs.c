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
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct amd8111e_priv {scalar_t__* rx_dma_addr; struct sk_buff** rx_skbuff; scalar_t__ rx_buff_len; int /*<<< orphan*/  pci_dev; scalar_t__* tx_dma_addr; struct sk_buff** tx_skbuff; } ;

/* Variables and functions */
 int NUM_RX_BUFFERS ; 
 int NUM_TX_BUFFERS ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd8111e_free_skbs(struct net_device *dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	struct sk_buff* rx_skbuff;
	int i;

	/* Freeing transmit skbs */
	for(i = 0; i < NUM_TX_BUFFERS; i++){
		if(lp->tx_skbuff[i]){
			pci_unmap_single(lp->pci_dev,lp->tx_dma_addr[i],					lp->tx_skbuff[i]->len,PCI_DMA_TODEVICE);
			dev_kfree_skb (lp->tx_skbuff[i]);
			lp->tx_skbuff[i] = NULL;
			lp->tx_dma_addr[i] = 0;
		}
	}
	/* Freeing previously allocated receive buffers */
	for (i = 0; i < NUM_RX_BUFFERS; i++){
		rx_skbuff = lp->rx_skbuff[i];
		if(rx_skbuff != NULL){
			pci_unmap_single(lp->pci_dev,lp->rx_dma_addr[i],
				  lp->rx_buff_len - 2,PCI_DMA_FROMDEVICE);
			dev_kfree_skb(lp->rx_skbuff[i]);
			lp->rx_skbuff[i] = NULL;
			lp->rx_dma_addr[i] = 0;
		}
	}

	return 0;
}