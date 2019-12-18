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
struct pci_dev {int dummy; } ;
struct mwl8k_priv {scalar_t__ fw_state; int /*<<< orphan*/  sram; int /*<<< orphan*/  regs; int /*<<< orphan*/  cookie_dma; int /*<<< orphan*/  cookie; int /*<<< orphan*/  pdev; int /*<<< orphan*/  poll_rx_task; int /*<<< orphan*/  poll_tx_task; int /*<<< orphan*/  firmware_loading_complete; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 scalar_t__ FW_STATE_ERROR ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_hw_reset (struct mwl8k_priv*) ; 
 int /*<<< orphan*/  mwl8k_rxq_deinit (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int mwl8k_tx_queues (struct mwl8k_priv*) ; 
 int /*<<< orphan*/  mwl8k_txq_deinit (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  mwl8k_txq_reclaim (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwl8k_remove(struct pci_dev *pdev)
{
	struct ieee80211_hw *hw = pci_get_drvdata(pdev);
	struct mwl8k_priv *priv;
	int i;

	if (hw == NULL)
		return;
	priv = hw->priv;

	wait_for_completion(&priv->firmware_loading_complete);

	if (priv->fw_state == FW_STATE_ERROR) {
		mwl8k_hw_reset(priv);
		goto unmap;
	}

	ieee80211_stop_queues(hw);

	ieee80211_unregister_hw(hw);

	/* Remove TX reclaim and RX tasklets.  */
	tasklet_kill(&priv->poll_tx_task);
	tasklet_kill(&priv->poll_rx_task);

	/* Stop hardware */
	mwl8k_hw_reset(priv);

	/* Return all skbs to mac80211 */
	for (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_reclaim(hw, i, INT_MAX, 1);

	for (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_deinit(hw, i);

	mwl8k_rxq_deinit(hw, 0);

	pci_free_consistent(priv->pdev, 4, priv->cookie, priv->cookie_dma);

unmap:
	pci_iounmap(pdev, priv->regs);
	pci_iounmap(pdev, priv->sram);
	pci_set_drvdata(pdev, NULL);
	ieee80211_free_hw(hw);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}