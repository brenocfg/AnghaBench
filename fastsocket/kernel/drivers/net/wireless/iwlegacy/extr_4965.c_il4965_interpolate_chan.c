#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  size_t u32 ;
struct il_priv {TYPE_4__* calib_info; } ;
struct il_eeprom_calib_measure {void* temperature; void* pa_det; void* gain_idx; void* actual_pow; } ;
struct il_eeprom_calib_ch_info {struct il_eeprom_calib_measure** measurements; void* ch_num; } ;
typedef  void* s8 ;
typedef  size_t s32 ;
struct TYPE_8__ {TYPE_3__* band_info; } ;
struct TYPE_6__ {size_t ch_num; struct il_eeprom_calib_measure** measurements; } ;
struct TYPE_5__ {size_t ch_num; struct il_eeprom_calib_measure** measurements; } ;
struct TYPE_7__ {TYPE_2__ ch2; TYPE_1__ ch1; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TXPOWER (char*,size_t,size_t,size_t,size_t,...) ; 
 size_t EEPROM_TX_POWER_BANDS ; 
 size_t EEPROM_TX_POWER_MEASUREMENTS ; 
 size_t EEPROM_TX_POWER_TX_CHAINS ; 
 int /*<<< orphan*/  IL_ERR (char*,size_t) ; 
 size_t il4965_get_sub_band (struct il_priv*,size_t) ; 
 scalar_t__ il4965_interpolate_value (size_t,size_t,void*,size_t,void*) ; 

__attribute__((used)) static int
il4965_interpolate_chan(struct il_priv *il, u32 channel,
			struct il_eeprom_calib_ch_info *chan_info)
{
	s32 s = -1;
	u32 c;
	u32 m;
	const struct il_eeprom_calib_measure *m1;
	const struct il_eeprom_calib_measure *m2;
	struct il_eeprom_calib_measure *omeas;
	u32 ch_i1;
	u32 ch_i2;

	s = il4965_get_sub_band(il, channel);
	if (s >= EEPROM_TX_POWER_BANDS) {
		IL_ERR("Tx Power can not find channel %d\n", channel);
		return -1;
	}

	ch_i1 = il->calib_info->band_info[s].ch1.ch_num;
	ch_i2 = il->calib_info->band_info[s].ch2.ch_num;
	chan_info->ch_num = (u8) channel;

	D_TXPOWER("channel %d subband %d factory cal ch %d & %d\n", channel, s,
		  ch_i1, ch_i2);

	for (c = 0; c < EEPROM_TX_POWER_TX_CHAINS; c++) {
		for (m = 0; m < EEPROM_TX_POWER_MEASUREMENTS; m++) {
			m1 = &(il->calib_info->band_info[s].ch1.
			       measurements[c][m]);
			m2 = &(il->calib_info->band_info[s].ch2.
			       measurements[c][m]);
			omeas = &(chan_info->measurements[c][m]);

			omeas->actual_pow =
			    (u8) il4965_interpolate_value(channel, ch_i1,
							  m1->actual_pow, ch_i2,
							  m2->actual_pow);
			omeas->gain_idx =
			    (u8) il4965_interpolate_value(channel, ch_i1,
							  m1->gain_idx, ch_i2,
							  m2->gain_idx);
			omeas->temperature =
			    (u8) il4965_interpolate_value(channel, ch_i1,
							  m1->temperature,
							  ch_i2,
							  m2->temperature);
			omeas->pa_det =
			    (s8) il4965_interpolate_value(channel, ch_i1,
							  m1->pa_det, ch_i2,
							  m2->pa_det);

			D_TXPOWER("chain %d meas %d AP1=%d AP2=%d AP=%d\n", c,
				  m, m1->actual_pow, m2->actual_pow,
				  omeas->actual_pow);
			D_TXPOWER("chain %d meas %d NI1=%d NI2=%d NI=%d\n", c,
				  m, m1->gain_idx, m2->gain_idx,
				  omeas->gain_idx);
			D_TXPOWER("chain %d meas %d PA1=%d PA2=%d PA=%d\n", c,
				  m, m1->pa_det, m2->pa_det, omeas->pa_det);
			D_TXPOWER("chain %d meas %d  T1=%d  T2=%d  T=%d\n", c,
				  m, m1->temperature, m2->temperature,
				  omeas->temperature);
		}
	}

	return 0;
}