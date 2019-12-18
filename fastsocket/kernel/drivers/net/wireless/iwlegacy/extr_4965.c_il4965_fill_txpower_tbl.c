#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* radio_tx_gain; int* dsp_predis_atten; } ;
union il4965_tx_power_dual_stream {int /*<<< orphan*/  dw; TYPE_4__ s; } ;
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_9__ {int /*<<< orphan*/ ** tx_atten; int /*<<< orphan*/  voltage; } ;
struct il_priv {int tx_power_user_lmt; TYPE_3__ card_alive_init; int /*<<< orphan*/  temperature; TYPE_2__* calib_info; int /*<<< orphan*/  band; } ;
struct il_eeprom_calib_measure {int temperature; int gain_idx; int actual_pow; } ;
struct il_eeprom_calib_ch_info {struct il_eeprom_calib_measure** measurements; } ;
struct il_channel_info {int ht40_max_power_avg; int max_power_avg; } ;
struct il4965_tx_power_db {TYPE_1__* power_tbl; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_12__ {int radio; int dsp; } ;
struct TYPE_11__ {int degrees_per_05db_a; int degrees_per_05db_a_denom; } ;
struct TYPE_8__ {scalar_t__ saturation_power24; scalar_t__ saturation_power52; int /*<<< orphan*/  voltage; } ;
struct TYPE_7__ {int /*<<< orphan*/  dw; } ;

/* Variables and functions */
 int CALIB_CH_GROUP_MAX ; 
 int /*<<< orphan*/  D_TXPOWER (char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 scalar_t__ IL_TX_POWER_CCK_COMPENSATION_C_STEP ; 
 int IL_TX_POWER_DEFAULT_REGULATORY_24 ; 
 int IL_TX_POWER_DEFAULT_REGULATORY_52 ; 
 scalar_t__ IL_TX_POWER_DEFAULT_SATURATION_24 ; 
 scalar_t__ IL_TX_POWER_DEFAULT_SATURATION_52 ; 
 int IL_TX_POWER_MIMO_REGULATORY_COMPENSATION ; 
 int IL_TX_POWER_REGULATORY_MAX ; 
 int IL_TX_POWER_REGULATORY_MIN ; 
 scalar_t__ IL_TX_POWER_SATURATION_MAX ; 
 scalar_t__ IL_TX_POWER_SATURATION_MIN ; 
 int /*<<< orphan*/  IL_TX_POWER_TEMPERATURE_MAX ; 
 int /*<<< orphan*/  IL_TX_POWER_TEMPERATURE_MIN ; 
 int /*<<< orphan*/  IL_WARN (char*,int) ; 
 int KELVIN_TO_CELSIUS (int) ; 
 int POWER_TBL_CCK_ENTRY ; 
 int POWER_TBL_NUM_ENTRIES ; 
 scalar_t__* back_off_table ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 TYPE_6__** gain_table ; 
 int get_min_power_idx (int,scalar_t__) ; 
 int il4965_get_tx_atten_grp (int) ; 
 int il4965_get_voltage_compensation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il4965_interpolate_chan (struct il_priv*,int,struct il_eeprom_calib_ch_info*) ; 
 int /*<<< orphan*/  il4965_math_div_round (int,int,int*) ; 
 struct il_channel_info* il_get_channel_info (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il_is_channel_valid (struct il_channel_info const*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* tx_power_cmp_tble ; 

__attribute__((used)) static int
il4965_fill_txpower_tbl(struct il_priv *il, u8 band, u16 channel, u8 is_ht40,
			u8 ctrl_chan_high,
			struct il4965_tx_power_db *tx_power_tbl)
{
	u8 saturation_power;
	s32 target_power;
	s32 user_target_power;
	s32 power_limit;
	s32 current_temp;
	s32 reg_limit;
	s32 current_regulatory;
	s32 txatten_grp = CALIB_CH_GROUP_MAX;
	int i;
	int c;
	const struct il_channel_info *ch_info = NULL;
	struct il_eeprom_calib_ch_info ch_eeprom_info;
	const struct il_eeprom_calib_measure *measurement;
	s16 voltage;
	s32 init_voltage;
	s32 voltage_compensation;
	s32 degrees_per_05db_num;
	s32 degrees_per_05db_denom;
	s32 factory_temp;
	s32 temperature_comp[2];
	s32 factory_gain_idx[2];
	s32 factory_actual_pwr[2];
	s32 power_idx;

	/* tx_power_user_lmt is in dBm, convert to half-dBm (half-dB units
	 *   are used for idxing into txpower table) */
	user_target_power = 2 * il->tx_power_user_lmt;

	/* Get current (RXON) channel, band, width */
	D_TXPOWER("chan %d band %d is_ht40 %d\n", channel, band, is_ht40);

	ch_info = il_get_channel_info(il, il->band, channel);

	if (!il_is_channel_valid(ch_info))
		return -EINVAL;

	/* get txatten group, used to select 1) thermal txpower adjustment
	 *   and 2) mimo txpower balance between Tx chains. */
	txatten_grp = il4965_get_tx_atten_grp(channel);
	if (txatten_grp < 0) {
		IL_ERR("Can't find txatten group for channel %d.\n", channel);
		return txatten_grp;
	}

	D_TXPOWER("channel %d belongs to txatten group %d\n", channel,
		  txatten_grp);

	if (is_ht40) {
		if (ctrl_chan_high)
			channel -= 2;
		else
			channel += 2;
	}

	/* hardware txpower limits ...
	 * saturation (clipping distortion) txpowers are in half-dBm */
	if (band)
		saturation_power = il->calib_info->saturation_power24;
	else
		saturation_power = il->calib_info->saturation_power52;

	if (saturation_power < IL_TX_POWER_SATURATION_MIN ||
	    saturation_power > IL_TX_POWER_SATURATION_MAX) {
		if (band)
			saturation_power = IL_TX_POWER_DEFAULT_SATURATION_24;
		else
			saturation_power = IL_TX_POWER_DEFAULT_SATURATION_52;
	}

	/* regulatory txpower limits ... reg_limit values are in half-dBm,
	 *   max_power_avg values are in dBm, convert * 2 */
	if (is_ht40)
		reg_limit = ch_info->ht40_max_power_avg * 2;
	else
		reg_limit = ch_info->max_power_avg * 2;

	if ((reg_limit < IL_TX_POWER_REGULATORY_MIN) ||
	    (reg_limit > IL_TX_POWER_REGULATORY_MAX)) {
		if (band)
			reg_limit = IL_TX_POWER_DEFAULT_REGULATORY_24;
		else
			reg_limit = IL_TX_POWER_DEFAULT_REGULATORY_52;
	}

	/* Interpolate txpower calibration values for this channel,
	 *   based on factory calibration tests on spaced channels. */
	il4965_interpolate_chan(il, channel, &ch_eeprom_info);

	/* calculate tx gain adjustment based on power supply voltage */
	voltage = le16_to_cpu(il->calib_info->voltage);
	init_voltage = (s32) le32_to_cpu(il->card_alive_init.voltage);
	voltage_compensation =
	    il4965_get_voltage_compensation(voltage, init_voltage);

	D_TXPOWER("curr volt %d eeprom volt %d volt comp %d\n", init_voltage,
		  voltage, voltage_compensation);

	/* get current temperature (Celsius) */
	current_temp = max(il->temperature, IL_TX_POWER_TEMPERATURE_MIN);
	current_temp = min(il->temperature, IL_TX_POWER_TEMPERATURE_MAX);
	current_temp = KELVIN_TO_CELSIUS(current_temp);

	/* select thermal txpower adjustment params, based on channel group
	 *   (same frequency group used for mimo txatten adjustment) */
	degrees_per_05db_num =
	    tx_power_cmp_tble[txatten_grp].degrees_per_05db_a;
	degrees_per_05db_denom =
	    tx_power_cmp_tble[txatten_grp].degrees_per_05db_a_denom;

	/* get per-chain txpower values from factory measurements */
	for (c = 0; c < 2; c++) {
		measurement = &ch_eeprom_info.measurements[c][1];

		/* txgain adjustment (in half-dB steps) based on difference
		 *   between factory and current temperature */
		factory_temp = measurement->temperature;
		il4965_math_div_round((current_temp -
				       factory_temp) * degrees_per_05db_denom,
				      degrees_per_05db_num,
				      &temperature_comp[c]);

		factory_gain_idx[c] = measurement->gain_idx;
		factory_actual_pwr[c] = measurement->actual_pow;

		D_TXPOWER("chain = %d\n", c);
		D_TXPOWER("fctry tmp %d, " "curr tmp %d, comp %d steps\n",
			  factory_temp, current_temp, temperature_comp[c]);

		D_TXPOWER("fctry idx %d, fctry pwr %d\n", factory_gain_idx[c],
			  factory_actual_pwr[c]);
	}

	/* for each of 33 bit-rates (including 1 for CCK) */
	for (i = 0; i < POWER_TBL_NUM_ENTRIES; i++) {
		u8 is_mimo_rate;
		union il4965_tx_power_dual_stream tx_power;

		/* for mimo, reduce each chain's txpower by half
		 * (3dB, 6 steps), so total output power is regulatory
		 * compliant. */
		if (i & 0x8) {
			current_regulatory =
			    reg_limit -
			    IL_TX_POWER_MIMO_REGULATORY_COMPENSATION;
			is_mimo_rate = 1;
		} else {
			current_regulatory = reg_limit;
			is_mimo_rate = 0;
		}

		/* find txpower limit, either hardware or regulatory */
		power_limit = saturation_power - back_off_table[i];
		if (power_limit > current_regulatory)
			power_limit = current_regulatory;

		/* reduce user's txpower request if necessary
		 * for this rate on this channel */
		target_power = user_target_power;
		if (target_power > power_limit)
			target_power = power_limit;

		D_TXPOWER("rate %d sat %d reg %d usr %d tgt %d\n", i,
			  saturation_power - back_off_table[i],
			  current_regulatory, user_target_power, target_power);

		/* for each of 2 Tx chains (radio transmitters) */
		for (c = 0; c < 2; c++) {
			s32 atten_value;

			if (is_mimo_rate)
				atten_value =
				    (s32) le32_to_cpu(il->card_alive_init.
						      tx_atten[txatten_grp][c]);
			else
				atten_value = 0;

			/* calculate idx; higher idx means lower txpower */
			power_idx =
			    (u8) (factory_gain_idx[c] -
				  (target_power - factory_actual_pwr[c]) -
				  temperature_comp[c] - voltage_compensation +
				  atten_value);

/*			D_TXPOWER("calculated txpower idx %d\n",
						power_idx); */

			if (power_idx < get_min_power_idx(i, band))
				power_idx = get_min_power_idx(i, band);

			/* adjust 5 GHz idx to support negative idxes */
			if (!band)
				power_idx += 9;

			/* CCK, rate 32, reduce txpower for CCK */
			if (i == POWER_TBL_CCK_ENTRY)
				power_idx +=
				    IL_TX_POWER_CCK_COMPENSATION_C_STEP;

			/* stay within the table! */
			if (power_idx > 107) {
				IL_WARN("txpower idx %d > 107\n", power_idx);
				power_idx = 107;
			}
			if (power_idx < 0) {
				IL_WARN("txpower idx %d < 0\n", power_idx);
				power_idx = 0;
			}

			/* fill txpower command for this rate/chain */
			tx_power.s.radio_tx_gain[c] =
			    gain_table[band][power_idx].radio;
			tx_power.s.dsp_predis_atten[c] =
			    gain_table[band][power_idx].dsp;

			D_TXPOWER("chain %d mimo %d idx %d "
				  "gain 0x%02x dsp %d\n", c, atten_value,
				  power_idx, tx_power.s.radio_tx_gain[c],
				  tx_power.s.dsp_predis_atten[c]);
		}		/* for each chain */

		tx_power_tbl->power_tbl[i].dw = cpu_to_le32(tx_power.dw);

	}			/* for each rate */

	return 0;
}