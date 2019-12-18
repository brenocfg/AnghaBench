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
typedef  int u8 ;
struct ieee80211_channel {scalar_t__ hw_value; scalar_t__ center_freq; } ;
struct ath5k_rate_pcal_info {int dummy; } ;
struct TYPE_2__ {int txp_requested; scalar_t__ txp_tpc; int /*<<< orphan*/  txp_setup; } ;
struct ath5k_hw {int ah_radio; TYPE_1__ ah_txpower; struct ieee80211_channel* ah_current_channel; } ;

/* Variables and functions */
 int AR5K_PHY_TXPOWER_RATE1 ; 
 int AR5K_PHY_TXPOWER_RATE2 ; 
 int AR5K_PHY_TXPOWER_RATE3 ; 
 int AR5K_PHY_TXPOWER_RATE4 ; 
 int AR5K_PHY_TXPOWER_RATE_MAX ; 
 int AR5K_PHY_TXPOWER_RATE_MAX_TPC_ENABLE ; 
 int AR5K_PWRTABLE_LINEAR_PCDAC ; 
 int AR5K_PWRTABLE_PWR_TO_PCDAC ; 
 int AR5K_PWRTABLE_PWR_TO_PDADC ; 
 int AR5K_REG_MS (int,int /*<<< orphan*/ ) ; 
#define  AR5K_RF2316 135 
#define  AR5K_RF2317 134 
#define  AR5K_RF2413 133 
#define  AR5K_RF2425 132 
#define  AR5K_RF5110 131 
#define  AR5K_RF5111 130 
#define  AR5K_RF5112 129 
#define  AR5K_RF5413 128 
 int AR5K_TPC ; 
 int /*<<< orphan*/  AR5K_TPC_ACK ; 
 int /*<<< orphan*/  AR5K_TPC_CHIRP ; 
 int /*<<< orphan*/  AR5K_TPC_CTS ; 
 int AR5K_TUNE_MAX_TXPOWER ; 
 scalar_t__ AR5K_TUNE_TPC_TXPOWER ; 
 int AR5K_TXPOWER_CCK (int,int) ; 
 int AR5K_TXPOWER_OFDM (int,int) ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*,int) ; 
 int EINVAL ; 
 int ath5k_eeprom_mode_from_channel (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ath5k_get_max_ctl_power (struct ath5k_hw*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ath5k_get_rate_pcal_data (struct ath5k_hw*,struct ieee80211_channel*,struct ath5k_rate_pcal_info*) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int) ; 
 int ath5k_setup_channel_powertable (struct ath5k_hw*,struct ieee80211_channel*,int,int) ; 
 int /*<<< orphan*/  ath5k_setup_rate_powertable (struct ath5k_hw*,int,struct ath5k_rate_pcal_info*,int) ; 
 int /*<<< orphan*/  ath5k_write_channel_powertable (struct ath5k_hw*,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ath5k_hw_txpower(struct ath5k_hw *ah, struct ieee80211_channel *channel,
		 u8 txpower)
{
	struct ath5k_rate_pcal_info rate_info;
	struct ieee80211_channel *curr_channel = ah->ah_current_channel;
	int ee_mode;
	u8 type;
	int ret;

	if (txpower > AR5K_TUNE_MAX_TXPOWER) {
		ATH5K_ERR(ah, "invalid tx power: %u\n", txpower);
		return -EINVAL;
	}

	ee_mode = ath5k_eeprom_mode_from_channel(ah, channel);

	/* Initialize TX power table */
	switch (ah->ah_radio) {
	case AR5K_RF5110:
		/* TODO */
		return 0;
	case AR5K_RF5111:
		type = AR5K_PWRTABLE_PWR_TO_PCDAC;
		break;
	case AR5K_RF5112:
		type = AR5K_PWRTABLE_LINEAR_PCDAC;
		break;
	case AR5K_RF2413:
	case AR5K_RF5413:
	case AR5K_RF2316:
	case AR5K_RF2317:
	case AR5K_RF2425:
		type = AR5K_PWRTABLE_PWR_TO_PDADC;
		break;
	default:
		return -EINVAL;
	}

	/*
	 * If we don't change channel/mode skip tx powertable calculation
	 * and use the cached one.
	 */
	if (!ah->ah_txpower.txp_setup ||
	    (channel->hw_value != curr_channel->hw_value) ||
	    (channel->center_freq != curr_channel->center_freq)) {
		/* Reset TX power values but preserve requested
		 * tx power from above */
		int requested_txpower = ah->ah_txpower.txp_requested;

		memset(&ah->ah_txpower, 0, sizeof(ah->ah_txpower));

		/* Restore TPC setting and requested tx power */
		ah->ah_txpower.txp_tpc = AR5K_TUNE_TPC_TXPOWER;

		ah->ah_txpower.txp_requested = requested_txpower;

		/* Calculate the powertable */
		ret = ath5k_setup_channel_powertable(ah, channel,
							ee_mode, type);
		if (ret)
			return ret;
	}

	/* Write table on hw */
	ath5k_write_channel_powertable(ah, ee_mode, type);

	/* Limit max power if we have a CTL available */
	ath5k_get_max_ctl_power(ah, channel);

	/* FIXME: Antenna reduction stuff */

	/* FIXME: Limit power on turbo modes */

	/* FIXME: TPC scale reduction */

	/* Get surrounding channels for per-rate power table
	 * calibration */
	ath5k_get_rate_pcal_data(ah, channel, &rate_info);

	/* Setup rate power table */
	ath5k_setup_rate_powertable(ah, txpower, &rate_info, ee_mode);

	/* Write rate power table on hw */
	ath5k_hw_reg_write(ah, AR5K_TXPOWER_OFDM(3, 24) |
		AR5K_TXPOWER_OFDM(2, 16) | AR5K_TXPOWER_OFDM(1, 8) |
		AR5K_TXPOWER_OFDM(0, 0), AR5K_PHY_TXPOWER_RATE1);

	ath5k_hw_reg_write(ah, AR5K_TXPOWER_OFDM(7, 24) |
		AR5K_TXPOWER_OFDM(6, 16) | AR5K_TXPOWER_OFDM(5, 8) |
		AR5K_TXPOWER_OFDM(4, 0), AR5K_PHY_TXPOWER_RATE2);

	ath5k_hw_reg_write(ah, AR5K_TXPOWER_CCK(10, 24) |
		AR5K_TXPOWER_CCK(9, 16) | AR5K_TXPOWER_CCK(15, 8) |
		AR5K_TXPOWER_CCK(8, 0), AR5K_PHY_TXPOWER_RATE3);

	ath5k_hw_reg_write(ah, AR5K_TXPOWER_CCK(14, 24) |
		AR5K_TXPOWER_CCK(13, 16) | AR5K_TXPOWER_CCK(12, 8) |
		AR5K_TXPOWER_CCK(11, 0), AR5K_PHY_TXPOWER_RATE4);

	/* FIXME: TPC support */
	if (ah->ah_txpower.txp_tpc) {
		ath5k_hw_reg_write(ah, AR5K_PHY_TXPOWER_RATE_MAX_TPC_ENABLE |
			AR5K_TUNE_MAX_TXPOWER, AR5K_PHY_TXPOWER_RATE_MAX);

		ath5k_hw_reg_write(ah,
			AR5K_REG_MS(AR5K_TUNE_MAX_TXPOWER, AR5K_TPC_ACK) |
			AR5K_REG_MS(AR5K_TUNE_MAX_TXPOWER, AR5K_TPC_CTS) |
			AR5K_REG_MS(AR5K_TUNE_MAX_TXPOWER, AR5K_TPC_CHIRP),
			AR5K_TPC);
	} else {
		ath5k_hw_reg_write(ah, AR5K_PHY_TXPOWER_RATE_MAX |
			AR5K_TUNE_MAX_TXPOWER, AR5K_PHY_TXPOWER_RATE_MAX);
	}

	return 0;
}