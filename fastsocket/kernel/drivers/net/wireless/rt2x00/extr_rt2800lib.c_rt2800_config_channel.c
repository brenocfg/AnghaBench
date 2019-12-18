#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  unsigned int u32 ;
struct TYPE_4__ {int tx_chain_num; int rx_chain_num; } ;
struct TYPE_3__ {int rf; } ;
struct rt2x00_dev {int lna_gain; int /*<<< orphan*/  cap_flags; TYPE_2__ default_ant; TYPE_1__ chip; } ;
struct rf_channel {int channel; } ;
struct ieee80211_conf {int dummy; } ;
struct channel_info {void* default_power2; void* default_power1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP3_HT40_MINUS ; 
 int /*<<< orphan*/  BBP49_UPDATE_FLAG ; 
 int /*<<< orphan*/  BBP4_BANDWIDTH ; 
 int /*<<< orphan*/  CAPABILITY_BT_COEXIST ; 
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_LNA_A ; 
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_LNA_BG ; 
 int /*<<< orphan*/  CH_BUSY_STA ; 
 int /*<<< orphan*/  CH_BUSY_STA_SEC ; 
 int /*<<< orphan*/  CH_IDLE_STA ; 
 int /*<<< orphan*/  REV_RT2860C ; 
#define  RF2020 141 
#define  RF3020 140 
#define  RF3021 139 
#define  RF3022 138 
#define  RF3052 137 
#define  RF3290 136 
#define  RF3320 135 
#define  RF3322 134 
#define  RF5360 133 
#define  RF5370 132 
#define  RF5372 131 
#define  RF5390 130 
#define  RF5392 129 
#define  RF5592 128 
 int /*<<< orphan*/  RFCSR30_RX_H20M ; 
 int /*<<< orphan*/  RFCSR30_TX_H20M ; 
 int /*<<< orphan*/  RFCSR3_VCOCAL_EN ; 
 int /*<<< orphan*/  RT2860 ; 
 int /*<<< orphan*/  RT3352 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  RT5390 ; 
 int /*<<< orphan*/  RT5392 ; 
 int /*<<< orphan*/  RT5592 ; 
 void* TXPOWER_A_TO_DEV (void*) ; 
 void* TXPOWER_G_TO_DEV (void*) ; 
 int /*<<< orphan*/  TX_BAND_CFG ; 
 int /*<<< orphan*/  TX_BAND_CFG_A ; 
 int /*<<< orphan*/  TX_BAND_CFG_BG ; 
 int /*<<< orphan*/  TX_BAND_CFG_HT40_MINUS ; 
 int /*<<< orphan*/  TX_PIN_CFG ; 
 int /*<<< orphan*/  TX_PIN_CFG_LNA_PE_A0_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_LNA_PE_A1_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_LNA_PE_G0_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_LNA_PE_G1_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_A0_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_A1_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_G0_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_PA_PE_G1_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_RFTR_EN ; 
 int /*<<< orphan*/  TX_PIN_CFG_TRSW_EN ; 
 int conf_is_ht40 (struct ieee80211_conf*) ; 
 int conf_is_ht40_minus (struct ieee80211_conf*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2800_bbp_read (struct rt2x00_dev*,int,int*) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write_with_rx_chain (struct rt2x00_dev*,int,unsigned int) ; 
 int /*<<< orphan*/  rt2800_config_channel_rf2xxx (struct rt2x00_dev*,struct ieee80211_conf*,struct rf_channel*,struct channel_info*) ; 
 int /*<<< orphan*/  rt2800_config_channel_rf3052 (struct rt2x00_dev*,struct ieee80211_conf*,struct rf_channel*,struct channel_info*) ; 
 int /*<<< orphan*/  rt2800_config_channel_rf3290 (struct rt2x00_dev*,struct ieee80211_conf*,struct rf_channel*,struct channel_info*) ; 
 int /*<<< orphan*/  rt2800_config_channel_rf3322 (struct rt2x00_dev*,struct ieee80211_conf*,struct rf_channel*,struct channel_info*) ; 
 int /*<<< orphan*/  rt2800_config_channel_rf3xxx (struct rt2x00_dev*,struct ieee80211_conf*,struct rf_channel*,struct channel_info*) ; 
 int /*<<< orphan*/  rt2800_config_channel_rf53xx (struct rt2x00_dev*,struct ieee80211_conf*,struct rf_channel*,struct channel_info*) ; 
 int /*<<< orphan*/  rt2800_config_channel_rf55xx (struct rt2x00_dev*,struct ieee80211_conf*,struct rf_channel*,struct channel_info*) ; 
 int /*<<< orphan*/  rt2800_iq_calibrate (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_read (struct rt2x00_dev*,int,int*) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 scalar_t__ rt2x00_rf (struct rt2x00_dev*,int const) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt_rev (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2800_config_channel(struct rt2x00_dev *rt2x00dev,
				  struct ieee80211_conf *conf,
				  struct rf_channel *rf,
				  struct channel_info *info)
{
	u32 reg;
	unsigned int tx_pin;
	u8 bbp, rfcsr;

	if (rf->channel <= 14) {
		info->default_power1 = TXPOWER_G_TO_DEV(info->default_power1);
		info->default_power2 = TXPOWER_G_TO_DEV(info->default_power2);
	} else {
		info->default_power1 = TXPOWER_A_TO_DEV(info->default_power1);
		info->default_power2 = TXPOWER_A_TO_DEV(info->default_power2);
	}

	switch (rt2x00dev->chip.rf) {
	case RF2020:
	case RF3020:
	case RF3021:
	case RF3022:
	case RF3320:
		rt2800_config_channel_rf3xxx(rt2x00dev, conf, rf, info);
		break;
	case RF3052:
		rt2800_config_channel_rf3052(rt2x00dev, conf, rf, info);
		break;
	case RF3290:
		rt2800_config_channel_rf3290(rt2x00dev, conf, rf, info);
		break;
	case RF3322:
		rt2800_config_channel_rf3322(rt2x00dev, conf, rf, info);
		break;
	case RF5360:
	case RF5370:
	case RF5372:
	case RF5390:
	case RF5392:
		rt2800_config_channel_rf53xx(rt2x00dev, conf, rf, info);
		break;
	case RF5592:
		rt2800_config_channel_rf55xx(rt2x00dev, conf, rf, info);
		break;
	default:
		rt2800_config_channel_rf2xxx(rt2x00dev, conf, rf, info);
	}

	if (rt2x00_rf(rt2x00dev, RF3290) ||
	    rt2x00_rf(rt2x00dev, RF3322) ||
	    rt2x00_rf(rt2x00dev, RF5360) ||
	    rt2x00_rf(rt2x00dev, RF5370) ||
	    rt2x00_rf(rt2x00dev, RF5372) ||
	    rt2x00_rf(rt2x00dev, RF5390) ||
	    rt2x00_rf(rt2x00dev, RF5392)) {
		rt2800_rfcsr_read(rt2x00dev, 30, &rfcsr);
		rt2x00_set_field8(&rfcsr, RFCSR30_TX_H20M, 0);
		rt2x00_set_field8(&rfcsr, RFCSR30_RX_H20M, 0);
		rt2800_rfcsr_write(rt2x00dev, 30, rfcsr);

		rt2800_rfcsr_read(rt2x00dev, 3, &rfcsr);
		rt2x00_set_field8(&rfcsr, RFCSR3_VCOCAL_EN, 1);
		rt2800_rfcsr_write(rt2x00dev, 3, rfcsr);
	}

	/*
	 * Change BBP settings
	 */
	if (rt2x00_rt(rt2x00dev, RT3352)) {
		rt2800_bbp_write(rt2x00dev, 27, 0x0);
		rt2800_bbp_write(rt2x00dev, 66, 0x26 + rt2x00dev->lna_gain);
		rt2800_bbp_write(rt2x00dev, 27, 0x20);
		rt2800_bbp_write(rt2x00dev, 66, 0x26 + rt2x00dev->lna_gain);
	} else {
		rt2800_bbp_write(rt2x00dev, 62, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_write(rt2x00dev, 63, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_write(rt2x00dev, 64, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_write(rt2x00dev, 86, 0);
	}

	if (rf->channel <= 14) {
		if (!rt2x00_rt(rt2x00dev, RT5390) &&
		    !rt2x00_rt(rt2x00dev, RT5392)) {
			if (test_bit(CAPABILITY_EXTERNAL_LNA_BG,
				     &rt2x00dev->cap_flags)) {
				rt2800_bbp_write(rt2x00dev, 82, 0x62);
				rt2800_bbp_write(rt2x00dev, 75, 0x46);
			} else {
				rt2800_bbp_write(rt2x00dev, 82, 0x84);
				rt2800_bbp_write(rt2x00dev, 75, 0x50);
			}
		}
	} else {
		if (rt2x00_rt(rt2x00dev, RT3572))
			rt2800_bbp_write(rt2x00dev, 82, 0x94);
		else
			rt2800_bbp_write(rt2x00dev, 82, 0xf2);

		if (test_bit(CAPABILITY_EXTERNAL_LNA_A, &rt2x00dev->cap_flags))
			rt2800_bbp_write(rt2x00dev, 75, 0x46);
		else
			rt2800_bbp_write(rt2x00dev, 75, 0x50);
	}

	rt2800_register_read(rt2x00dev, TX_BAND_CFG, &reg);
	rt2x00_set_field32(&reg, TX_BAND_CFG_HT40_MINUS, conf_is_ht40_minus(conf));
	rt2x00_set_field32(&reg, TX_BAND_CFG_A, rf->channel > 14);
	rt2x00_set_field32(&reg, TX_BAND_CFG_BG, rf->channel <= 14);
	rt2800_register_write(rt2x00dev, TX_BAND_CFG, reg);

	if (rt2x00_rt(rt2x00dev, RT3572))
		rt2800_rfcsr_write(rt2x00dev, 8, 0);

	tx_pin = 0;

	/* Turn on unused PA or LNA when not using 1T or 1R */
	if (rt2x00dev->default_ant.tx_chain_num == 2) {
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A1_EN,
				   rf->channel > 14);
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G1_EN,
				   rf->channel <= 14);
	}

	/* Turn on unused PA or LNA when not using 1T or 1R */
	if (rt2x00dev->default_ant.rx_chain_num == 2) {
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_A1_EN, 1);
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_G1_EN, 1);
	}

	rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_A0_EN, 1);
	rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_G0_EN, 1);
	rt2x00_set_field32(&tx_pin, TX_PIN_CFG_RFTR_EN, 1);
	rt2x00_set_field32(&tx_pin, TX_PIN_CFG_TRSW_EN, 1);
	if (test_bit(CAPABILITY_BT_COEXIST, &rt2x00dev->cap_flags))
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN, 1);
	else
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN,
				   rf->channel <= 14);
	rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A0_EN, rf->channel > 14);

	rt2800_register_write(rt2x00dev, TX_PIN_CFG, tx_pin);

	if (rt2x00_rt(rt2x00dev, RT3572))
		rt2800_rfcsr_write(rt2x00dev, 8, 0x80);

	if (rt2x00_rt(rt2x00dev, RT5592)) {
		rt2800_bbp_write(rt2x00dev, 195, 141);
		rt2800_bbp_write(rt2x00dev, 196, conf_is_ht40(conf) ? 0x10 : 0x1a);

		/* AGC init */
		reg = (rf->channel <= 14 ? 0x1c : 0x24) + 2 * rt2x00dev->lna_gain;
		rt2800_bbp_write_with_rx_chain(rt2x00dev, 66, reg);

		rt2800_iq_calibrate(rt2x00dev, rf->channel);
	}

	rt2800_bbp_read(rt2x00dev, 4, &bbp);
	rt2x00_set_field8(&bbp, BBP4_BANDWIDTH, 2 * conf_is_ht40(conf));
	rt2800_bbp_write(rt2x00dev, 4, bbp);

	rt2800_bbp_read(rt2x00dev, 3, &bbp);
	rt2x00_set_field8(&bbp, BBP3_HT40_MINUS, conf_is_ht40_minus(conf));
	rt2800_bbp_write(rt2x00dev, 3, bbp);

	if (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860C)) {
		if (conf_is_ht40(conf)) {
			rt2800_bbp_write(rt2x00dev, 69, 0x1a);
			rt2800_bbp_write(rt2x00dev, 70, 0x0a);
			rt2800_bbp_write(rt2x00dev, 73, 0x16);
		} else {
			rt2800_bbp_write(rt2x00dev, 69, 0x16);
			rt2800_bbp_write(rt2x00dev, 70, 0x08);
			rt2800_bbp_write(rt2x00dev, 73, 0x11);
		}
	}

	msleep(1);

	/*
	 * Clear channel statistic counters
	 */
	rt2800_register_read(rt2x00dev, CH_IDLE_STA, &reg);
	rt2800_register_read(rt2x00dev, CH_BUSY_STA, &reg);
	rt2800_register_read(rt2x00dev, CH_BUSY_STA_SEC, &reg);

	/*
	 * Clear update flag
	 */
	if (rt2x00_rt(rt2x00dev, RT3352)) {
		rt2800_bbp_read(rt2x00dev, 49, &bbp);
		rt2x00_set_field8(&bbp, BBP49_UPDATE_FLAG, 0);
		rt2800_bbp_write(rt2x00dev, 49, bbp);
	}
}