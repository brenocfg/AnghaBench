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
typedef  size_t u8 ;
struct il_priv {scalar_t__ tx_power_user_lmt; size_t channel_count; struct il_channel_info* channel_info; } ;
struct il_channel_info {scalar_t__ curr_txpow; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  D_POWER (char*,scalar_t__) ; 
 int /*<<< orphan*/  il3945_hw_reg_comp_txpower_temp (struct il_priv*) ; 
 scalar_t__ il3945_hw_reg_get_ch_txpower_limit (struct il_channel_info*) ; 
 int /*<<< orphan*/  il3945_hw_reg_set_new_power (struct il_priv*,struct il_channel_info*) ; 
 int /*<<< orphan*/  il3945_is_temp_calib_needed (struct il_priv*) ; 
 size_t il_is_channel_a_band (struct il_channel_info*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

int
il3945_hw_reg_set_txpower(struct il_priv *il, s8 power)
{
	struct il_channel_info *ch_info;
	s8 max_power;
	u8 a_band;
	u8 i;

	if (il->tx_power_user_lmt == power) {
		D_POWER("Requested Tx power same as current " "limit: %ddBm.\n",
			power);
		return 0;
	}

	D_POWER("Setting upper limit clamp to %ddBm.\n", power);
	il->tx_power_user_lmt = power;

	/* set up new Tx powers for each and every channel, 2.4 and 5.x */

	for (i = 0; i < il->channel_count; i++) {
		ch_info = &il->channel_info[i];
		a_band = il_is_channel_a_band(ch_info);

		/* find minimum power of all user and regulatory constraints
		 *    (does not consider h/w clipping limitations) */
		max_power = il3945_hw_reg_get_ch_txpower_limit(ch_info);
		max_power = min(power, max_power);
		if (max_power != ch_info->curr_txpow) {
			ch_info->curr_txpow = max_power;

			/* this considers the h/w clipping limitations */
			il3945_hw_reg_set_new_power(il, ch_info);
		}
	}

	/* update txpower settings for all channels,
	 *   send to NIC if associated. */
	il3945_is_temp_calib_needed(il);
	il3945_hw_reg_comp_txpower_temp(il);

	return 0;
}