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
struct mwl8k_rx_queue {scalar_t__ rxd_dma; int /*<<< orphan*/ * rxd; int /*<<< orphan*/ * buf; scalar_t__ tail; scalar_t__ head; scalar_t__ rxd_count; } ;
struct mwl8k_priv {TYPE_1__* rxd_ops; int /*<<< orphan*/  pdev; struct mwl8k_rx_queue* rxq; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mwl8k_priv* priv; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int rxd_size; int /*<<< orphan*/  (* rxd_init ) (void*,scalar_t__) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_RX_DESCS ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (void*,scalar_t__) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mwl8k_rxq_init(struct ieee80211_hw *hw, int index)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_rx_queue *rxq = priv->rxq + index;
	int size;
	int i;

	rxq->rxd_count = 0;
	rxq->head = 0;
	rxq->tail = 0;

	size = MWL8K_RX_DESCS * priv->rxd_ops->rxd_size;

	rxq->rxd = pci_alloc_consistent(priv->pdev, size, &rxq->rxd_dma);
	if (rxq->rxd == NULL) {
		wiphy_err(hw->wiphy, "failed to alloc RX descriptors\n");
		return -ENOMEM;
	}
	memset(rxq->rxd, 0, size);

	rxq->buf = kcalloc(MWL8K_RX_DESCS, sizeof(*rxq->buf), GFP_KERNEL);
	if (rxq->buf == NULL) {
		pci_free_consistent(priv->pdev, size, rxq->rxd, rxq->rxd_dma);
		return -ENOMEM;
	}

	for (i = 0; i < MWL8K_RX_DESCS; i++) {
		int desc_size;
		void *rxd;
		int nexti;
		dma_addr_t next_dma_addr;

		desc_size = priv->rxd_ops->rxd_size;
		rxd = rxq->rxd + (i * priv->rxd_ops->rxd_size);

		nexti = i + 1;
		if (nexti == MWL8K_RX_DESCS)
			nexti = 0;
		next_dma_addr = rxq->rxd_dma + (nexti * desc_size);

		priv->rxd_ops->rxd_init(rxd, next_dma_addr);
	}

	return 0;
}