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
struct TYPE_2__ {int cck_basic_rates; int ofdm_basic_rates; } ;
struct il_priv {int active_rate; TYPE_1__ staging; int /*<<< orphan*/  band; } ;
struct ieee80211_supported_band {int n_bitrates; struct ieee80211_rate* bitrates; } ;
struct ieee80211_rate {int hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_RATE (char*,int) ; 
 int IL_CCK_BASIC_RATES_MASK ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int IL_FIRST_CCK_RATE ; 
 int IL_FIRST_OFDM_RATE ; 
 int IL_OFDM_BASIC_RATES_MASK ; 
 int RATE_COUNT_LEGACY ; 
 struct ieee80211_supported_band* il_get_hw_mode (struct il_priv*,int /*<<< orphan*/ ) ; 

void
il_set_rate(struct il_priv *il)
{
	const struct ieee80211_supported_band *hw = NULL;
	struct ieee80211_rate *rate;
	int i;

	hw = il_get_hw_mode(il, il->band);
	if (!hw) {
		IL_ERR("Failed to set rate: unable to get hw mode\n");
		return;
	}

	il->active_rate = 0;

	for (i = 0; i < hw->n_bitrates; i++) {
		rate = &(hw->bitrates[i]);
		if (rate->hw_value < RATE_COUNT_LEGACY)
			il->active_rate |= (1 << rate->hw_value);
	}

	D_RATE("Set active_rate = %0x\n", il->active_rate);

	il->staging.cck_basic_rates =
	    (IL_CCK_BASIC_RATES_MASK >> IL_FIRST_CCK_RATE) & 0xF;

	il->staging.ofdm_basic_rates =
	    (IL_OFDM_BASIC_RATES_MASK >> IL_FIRST_OFDM_RATE) & 0xFF;
}