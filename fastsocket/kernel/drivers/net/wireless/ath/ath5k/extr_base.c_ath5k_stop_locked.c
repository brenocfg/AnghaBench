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
struct ath5k_hw {int /*<<< orphan*/  irq; int /*<<< orphan*/  status; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_RESET ; 
 int /*<<< orphan*/  ATH_STAT_INVALID ; 
 int /*<<< orphan*/  ath5k_drain_tx_buffs (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_dma_stop (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_phy_disable (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_imr (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_led_off (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_rx_stop (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath5k_stop_locked(struct ath5k_hw *ah)
{

	ATH5K_DBG(ah, ATH5K_DEBUG_RESET, "invalid %u\n",
			test_bit(ATH_STAT_INVALID, ah->status));

	/*
	 * Shutdown the hardware and driver:
	 *    stop output from above
	 *    disable interrupts
	 *    turn off timers
	 *    turn off the radio
	 *    clear transmit machinery
	 *    clear receive machinery
	 *    drain and release tx queues
	 *    reclaim beacon resources
	 *    power down hardware
	 *
	 * Note that some of this work is not possible if the
	 * hardware is gone (invalid).
	 */
	ieee80211_stop_queues(ah->hw);

	if (!test_bit(ATH_STAT_INVALID, ah->status)) {
		ath5k_led_off(ah);
		ath5k_hw_set_imr(ah, 0);
		synchronize_irq(ah->irq);
		ath5k_rx_stop(ah);
		ath5k_hw_dma_stop(ah);
		ath5k_drain_tx_buffs(ah);
		ath5k_hw_phy_disable(ah);
	}

	return 0;
}