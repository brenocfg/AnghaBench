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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_hw {int /*<<< orphan*/  filter_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_RX_FILTER_BEACON ; 
 int /*<<< orphan*/  ath5k_hw_get_rx_filter (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_rx_filter (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

void
ath5k_set_beacon_filter(struct ieee80211_hw *hw, bool enable)
{
	struct ath5k_hw *ah = hw->priv;
	u32 rfilt;
	rfilt = ath5k_hw_get_rx_filter(ah);
	if (enable)
		rfilt |= AR5K_RX_FILTER_BEACON;
	else
		rfilt &= ~AR5K_RX_FILTER_BEACON;
	ath5k_hw_set_rx_filter(ah, rfilt);
	ah->filter_flags = rfilt;
}