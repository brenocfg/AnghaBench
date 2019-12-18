#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {size_t free_data_tx; scalar_t__* pci_map_tx_address; int /*<<< orphan*/  pdev; struct sk_buff** data_low_tx; } ;
typedef  TYPE_1__ islpci_private ;
struct TYPE_6__ {int /*<<< orphan*/ * device_curr_frag; } ;
typedef  TYPE_2__ isl38xx_control_block ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ISL38XX_CB_TX_DATA_LQ ; 
 size_t ISL38XX_CB_TX_QSIZE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  SHOW_TRACING ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
islpci_eth_cleanup_transmit(islpci_private *priv,
			    isl38xx_control_block *control_block)
{
	struct sk_buff *skb;
	u32 index;

	/* compare the control block read pointer with the free pointer */
	while (priv->free_data_tx !=
	       le32_to_cpu(control_block->
			   device_curr_frag[ISL38XX_CB_TX_DATA_LQ])) {
		/* read the index of the first fragment to be freed */
		index = priv->free_data_tx % ISL38XX_CB_TX_QSIZE;

		/* check for holes in the arrays caused by multi fragment frames
		 * searching for the last fragment of a frame */
		if (priv->pci_map_tx_address[index]) {
			/* entry is the last fragment of a frame
			 * free the skb structure and unmap pci memory */
			skb = priv->data_low_tx[index];

#if VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING,
			      "cleanup skb %p skb->data %p skb->len %u truesize %u\n ",
			      skb, skb->data, skb->len, skb->truesize);
#endif

			pci_unmap_single(priv->pdev,
					 priv->pci_map_tx_address[index],
					 skb->len, PCI_DMA_TODEVICE);
			dev_kfree_skb_irq(skb);
			skb = NULL;
		}
		/* increment the free data low queue pointer */
		priv->free_data_tx++;
	}
}