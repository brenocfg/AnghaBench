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
struct mwl8k_priv {int irq; int /*<<< orphan*/  poll_rx_task; int /*<<< orphan*/  poll_tx_task; int /*<<< orphan*/ * beacon_skb; int /*<<< orphan*/  watchdog_ba_handle; int /*<<< orphan*/  finalize_join_worker; TYPE_1__* pdev; scalar_t__ regs; int /*<<< orphan*/  hw_restart_in_progress; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_MASK ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mwl8k_cmd_radio_disable (struct ieee80211_hw*) ; 
 int mwl8k_tx_queues (struct mwl8k_priv*) ; 
 int /*<<< orphan*/  mwl8k_txq_reclaim (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwl8k_stop(struct ieee80211_hw *hw)
{
	struct mwl8k_priv *priv = hw->priv;
	int i;

	if (!priv->hw_restart_in_progress)
		mwl8k_cmd_radio_disable(hw);

	ieee80211_stop_queues(hw);

	/* Disable interrupts */
	iowrite32(0, priv->regs + MWL8K_HIU_A2H_INTERRUPT_MASK);
	if (priv->irq != -1) {
		free_irq(priv->pdev->irq, hw);
		priv->irq = -1;
	}

	/* Stop finalize join worker */
	cancel_work_sync(&priv->finalize_join_worker);
	cancel_work_sync(&priv->watchdog_ba_handle);
	if (priv->beacon_skb != NULL)
		dev_kfree_skb(priv->beacon_skb);

	/* Stop TX reclaim and RX tasklets.  */
	tasklet_disable(&priv->poll_tx_task);
	tasklet_disable(&priv->poll_rx_task);

	/* Return all skbs to mac80211 */
	for (i = 0; i < mwl8k_tx_queues(priv); i++)
		mwl8k_txq_reclaim(hw, i, INT_MAX, 1);
}