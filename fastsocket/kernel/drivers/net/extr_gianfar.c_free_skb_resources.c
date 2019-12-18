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
struct txbd8 {int /*<<< orphan*/  length; scalar_t__ bufPtr; scalar_t__ lstatus; } ;
struct rxbd8 {scalar_t__ bufPtr; scalar_t__ lstatus; } ;
struct gfar_private {int tx_ring_size; int rx_ring_size; int /*<<< orphan*/ ** rx_skbuff; int /*<<< orphan*/  rx_buffer_size; TYPE_1__* ofdev; struct rxbd8* rx_bd_base; int /*<<< orphan*/ ** tx_skbuff; struct txbd8* tx_bd_base; } ;
struct TYPE_4__ {int nr_frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 TYPE_2__* skb_shinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_skb_resources(struct gfar_private *priv)
{
	struct rxbd8 *rxbdp;
	struct txbd8 *txbdp;
	int i, j;

	/* Go through all the buffer descriptors and free their data buffers */
	txbdp = priv->tx_bd_base;

	for (i = 0; i < priv->tx_ring_size; i++) {
		if (!priv->tx_skbuff[i])
			continue;

		dma_unmap_single(&priv->ofdev->dev, txbdp->bufPtr,
				txbdp->length, DMA_TO_DEVICE);
		txbdp->lstatus = 0;
		for (j = 0; j < skb_shinfo(priv->tx_skbuff[i])->nr_frags; j++) {
			txbdp++;
			dma_unmap_page(&priv->ofdev->dev, txbdp->bufPtr,
					txbdp->length, DMA_TO_DEVICE);
		}
		txbdp++;
		dev_kfree_skb_any(priv->tx_skbuff[i]);
		priv->tx_skbuff[i] = NULL;
	}

	kfree(priv->tx_skbuff);

	rxbdp = priv->rx_bd_base;

	/* rx_skbuff is not guaranteed to be allocated, so only
	 * free it and its contents if it is allocated */
	if(priv->rx_skbuff != NULL) {
		for (i = 0; i < priv->rx_ring_size; i++) {
			if (priv->rx_skbuff[i]) {
				dma_unmap_single(&priv->ofdev->dev, rxbdp->bufPtr,
						priv->rx_buffer_size,
						DMA_FROM_DEVICE);

				dev_kfree_skb_any(priv->rx_skbuff[i]);
				priv->rx_skbuff[i] = NULL;
			}

			rxbdp->lstatus = 0;
			rxbdp->bufPtr = 0;

			rxbdp++;
		}

		kfree(priv->rx_skbuff);
	}
}