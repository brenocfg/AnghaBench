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
struct mwl8k_tx_queue {int /*<<< orphan*/ * txd; int /*<<< orphan*/  txd_dma; int /*<<< orphan*/ * skb; } ;
struct mwl8k_tx_desc {int dummy; } ;
struct mwl8k_priv {int /*<<< orphan*/  pdev; struct mwl8k_tx_queue* txq; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int MWL8K_TX_DESCS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwl8k_txq_reclaim (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwl8k_txq_deinit(struct ieee80211_hw *hw, int index)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_tx_queue *txq = priv->txq + index;

	if (txq->txd == NULL)
		return;

	mwl8k_txq_reclaim(hw, index, INT_MAX, 1);

	kfree(txq->skb);
	txq->skb = NULL;

	pci_free_consistent(priv->pdev,
			    MWL8K_TX_DESCS * sizeof(struct mwl8k_tx_desc),
			    txq->txd, txq->txd_dma);
	txq->txd = NULL;
}