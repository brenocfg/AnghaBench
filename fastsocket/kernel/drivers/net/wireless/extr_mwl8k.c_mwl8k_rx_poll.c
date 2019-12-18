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
struct mwl8k_priv {int /*<<< orphan*/  poll_rx_task; scalar_t__ regs; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWL8K_A2H_INT_RX_READY ; 
 scalar_t__ MWL8K_HIU_A2H_INTERRUPT_STATUS ; 
 scalar_t__ rxq_process (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rxq_refill (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mwl8k_rx_poll(unsigned long data)
{
	struct ieee80211_hw *hw = (struct ieee80211_hw *)data;
	struct mwl8k_priv *priv = hw->priv;
	int limit;

	limit = 32;
	limit -= rxq_process(hw, 0, limit);
	limit -= rxq_refill(hw, 0, limit);

	if (limit) {
		writel(~MWL8K_A2H_INT_RX_READY,
		       priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	} else {
		tasklet_schedule(&priv->poll_rx_task);
	}
}