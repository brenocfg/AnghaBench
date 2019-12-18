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
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  chan; } ;
struct ieee80211_conf {int power_level; int /*<<< orphan*/  short_frame_max_tx_count; int /*<<< orphan*/  long_frame_max_tx_count; TYPE_1__ chandef; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct ath5k_hw* priv; } ;
struct TYPE_7__ {int q_tx_num; } ;
struct TYPE_8__ {TYPE_3__ cap_queues; } ;
struct TYPE_6__ {int txp_requested; } ;
struct ath5k_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  ah_ant_mode; TYPE_4__ ah_capabilities; int /*<<< orphan*/  ah_retry_short; int /*<<< orphan*/  ah_retry_long; TYPE_2__ ah_txpower; } ;

/* Variables and functions */
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_POWER ; 
 int IEEE80211_CONF_CHANGE_RETRY_LIMITS ; 
 int ath5k_chan_set (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_set_antenna_mode (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_set_tx_retry_limits (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_hw_set_txpower_limit (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath5k_config(struct ieee80211_hw *hw, u32 changed)
{
	struct ath5k_hw *ah = hw->priv;
	struct ieee80211_conf *conf = &hw->conf;
	int ret = 0;
	int i;

	mutex_lock(&ah->lock);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		ret = ath5k_chan_set(ah, conf->chandef.chan);
		if (ret < 0)
			goto unlock;
	}

	if ((changed & IEEE80211_CONF_CHANGE_POWER) &&
	(ah->ah_txpower.txp_requested != conf->power_level)) {
		ah->ah_txpower.txp_requested = conf->power_level;

		/* Half dB steps */
		ath5k_hw_set_txpower_limit(ah, (conf->power_level * 2));
	}

	if (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS) {
		ah->ah_retry_long = conf->long_frame_max_tx_count;
		ah->ah_retry_short = conf->short_frame_max_tx_count;

		for (i = 0; i < ah->ah_capabilities.cap_queues.q_tx_num; i++)
			ath5k_hw_set_tx_retry_limits(ah, i);
	}

	/* TODO:
	 * 1) Move this on config_interface and handle each case
	 * separately eg. when we have only one STA vif, use
	 * AR5K_ANTMODE_SINGLE_AP
	 *
	 * 2) Allow the user to change antenna mode eg. when only
	 * one antenna is present
	 *
	 * 3) Allow the user to set default/tx antenna when possible
	 *
	 * 4) Default mode should handle 90% of the cases, together
	 * with fixed a/b and single AP modes we should be able to
	 * handle 99%. Sectored modes are extreme cases and i still
	 * haven't found a usage for them. If we decide to support them,
	 * then we must allow the user to set how many tx antennas we
	 * have available
	 */
	ath5k_hw_set_antenna_mode(ah, ah->ah_ant_mode);

unlock:
	mutex_unlock(&ah->lock);
	return ret;
}