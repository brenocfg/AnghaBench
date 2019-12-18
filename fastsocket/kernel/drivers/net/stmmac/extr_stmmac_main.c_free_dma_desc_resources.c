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
struct stmmac_priv {int dma_tx_size; int dma_rx_size; int /*<<< orphan*/  tx_skbuff; int /*<<< orphan*/  rx_skbuff; int /*<<< orphan*/  rx_skbuff_dma; int /*<<< orphan*/  dma_rx_phy; int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  device; int /*<<< orphan*/  dma_tx_phy; int /*<<< orphan*/  dma_tx; } ;
struct dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_rx_skbufs (struct stmmac_priv*) ; 
 int /*<<< orphan*/  dma_free_tx_skbufs (struct stmmac_priv*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_dma_desc_resources(struct stmmac_priv *priv)
{
	/* Release the DMA TX/RX socket buffers */
	dma_free_rx_skbufs(priv);
	dma_free_tx_skbufs(priv);

	/* Free the region of consistent memory previously allocated for
	 * the DMA */
	dma_free_coherent(priv->device,
			  priv->dma_tx_size * sizeof(struct dma_desc),
			  priv->dma_tx, priv->dma_tx_phy);
	dma_free_coherent(priv->device,
			  priv->dma_rx_size * sizeof(struct dma_desc),
			  priv->dma_rx, priv->dma_rx_phy);
	kfree(priv->rx_skbuff_dma);
	kfree(priv->rx_skbuff);
	kfree(priv->tx_skbuff);

	return;
}