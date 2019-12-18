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
struct survey_info {int filled; int /*<<< orphan*/  noise; int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct ieee80211_conf {TYPE_1__ chandef; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct ath5k_hw* priv; } ;
struct ath_cycle_counters {unsigned int cycles; unsigned int rx_busy; unsigned int rx_frame; unsigned int tx_frame; } ;
struct ath_common {int clockrate; int /*<<< orphan*/  cc_lock; struct ath_cycle_counters cc_survey; } ;
struct TYPE_4__ {unsigned int channel_time; unsigned int channel_time_busy; unsigned int channel_time_rx; unsigned int channel_time_tx; } ;
struct ath5k_hw {int /*<<< orphan*/  ah_noise_floor; TYPE_2__ survey; } ;

/* Variables and functions */
 int ENOENT ; 
 int SURVEY_INFO_CHANNEL_TIME ; 
 int SURVEY_INFO_CHANNEL_TIME_BUSY ; 
 int SURVEY_INFO_CHANNEL_TIME_RX ; 
 int SURVEY_INFO_CHANNEL_TIME_TX ; 
 int SURVEY_INFO_NOISE_DBM ; 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath_hw_cycle_counters_update (struct ath_common*) ; 
 int /*<<< orphan*/  memcpy (struct survey_info*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (struct ath_cycle_counters*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ath5k_get_survey(struct ieee80211_hw *hw, int idx, struct survey_info *survey)
{
	struct ath5k_hw *ah = hw->priv;
	struct ieee80211_conf *conf = &hw->conf;
	struct ath_common *common = ath5k_hw_common(ah);
	struct ath_cycle_counters *cc = &common->cc_survey;
	unsigned int div = common->clockrate * 1000;

	if (idx != 0)
		return -ENOENT;

	spin_lock_bh(&common->cc_lock);
	ath_hw_cycle_counters_update(common);
	if (cc->cycles > 0) {
		ah->survey.channel_time += cc->cycles / div;
		ah->survey.channel_time_busy += cc->rx_busy / div;
		ah->survey.channel_time_rx += cc->rx_frame / div;
		ah->survey.channel_time_tx += cc->tx_frame / div;
	}
	memset(cc, 0, sizeof(*cc));
	spin_unlock_bh(&common->cc_lock);

	memcpy(survey, &ah->survey, sizeof(*survey));

	survey->channel = conf->chandef.chan;
	survey->noise = ah->ah_noise_floor;
	survey->filled = SURVEY_INFO_NOISE_DBM |
			SURVEY_INFO_CHANNEL_TIME |
			SURVEY_INFO_CHANNEL_TIME_BUSY |
			SURVEY_INFO_CHANNEL_TIME_RX |
			SURVEY_INFO_CHANNEL_TIME_TX;

	return 0;
}