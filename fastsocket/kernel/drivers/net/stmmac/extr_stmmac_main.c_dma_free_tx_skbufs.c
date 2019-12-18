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
struct stmmac_priv {int dma_tx_size; int /*<<< orphan*/ ** tx_skbuff; TYPE_2__* mac_type; int /*<<< orphan*/  device; struct dma_desc* dma_tx; } ;
struct dma_desc {scalar_t__ des2; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_tx_len ) (struct dma_desc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dma_desc*) ; 

__attribute__((used)) static void dma_free_tx_skbufs(struct stmmac_priv *priv)
{
	int i;

	for (i = 0; i < priv->dma_tx_size; i++) {
		if (priv->tx_skbuff[i] != NULL) {
			struct dma_desc *p = priv->dma_tx + i;
			if (p->des2)
				dma_unmap_single(priv->device, p->des2,
				 priv->mac_type->ops->get_tx_len(p),
				 DMA_TO_DEVICE);
			dev_kfree_skb_any(priv->tx_skbuff[i]);
			priv->tx_skbuff[i] = NULL;
		}
	}
	return;
}