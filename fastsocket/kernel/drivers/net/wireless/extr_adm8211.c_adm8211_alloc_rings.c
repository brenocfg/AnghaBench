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
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {int rx_ring_size; int tx_ring_size; scalar_t__ rx_ring_dma; scalar_t__ tx_ring_dma; scalar_t__ rx_ring; struct adm8211_desc* tx_ring; int /*<<< orphan*/ * tx_buffers; int /*<<< orphan*/ * rx_buffers; int /*<<< orphan*/  pdev; } ;
struct adm8211_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_consistent (int /*<<< orphan*/ ,unsigned int,scalar_t__*) ; 

__attribute__((used)) static int adm8211_alloc_rings(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;
	unsigned int ring_size;

	priv->rx_buffers = kmalloc(sizeof(*priv->rx_buffers) * priv->rx_ring_size +
				   sizeof(*priv->tx_buffers) * priv->tx_ring_size, GFP_KERNEL);
	if (!priv->rx_buffers)
		return -ENOMEM;

	priv->tx_buffers = (void *)priv->rx_buffers +
			   sizeof(*priv->rx_buffers) * priv->rx_ring_size;

	/* Allocate TX/RX descriptors */
	ring_size = sizeof(struct adm8211_desc) * priv->rx_ring_size +
		    sizeof(struct adm8211_desc) * priv->tx_ring_size;
	priv->rx_ring = pci_alloc_consistent(priv->pdev, ring_size,
					     &priv->rx_ring_dma);

	if (!priv->rx_ring) {
		kfree(priv->rx_buffers);
		priv->rx_buffers = NULL;
		priv->tx_buffers = NULL;
		return -ENOMEM;
	}

	priv->tx_ring = (struct adm8211_desc *)(priv->rx_ring +
						priv->rx_ring_size);
	priv->tx_ring_dma = priv->rx_ring_dma +
			    sizeof(struct adm8211_desc) * priv->rx_ring_size;

	return 0;
}