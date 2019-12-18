#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_8__ {scalar_t__ flags; int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {int is_40mhz; int /*<<< orphan*/  extension_chan_offset; } ;
struct il_ht_config {int /*<<< orphan*/  smps; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel; } ;
struct il_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  vif; scalar_t__ switch_channel; int /*<<< orphan*/  status; TYPE_4__* ops; int /*<<< orphan*/  lock; TYPE_3__ staging; TYPE_2__ ht; struct il_ht_config current_ht_config; TYPE_1__ active; } ;
struct il_channel_info {int dummy; } ;
struct ieee80211_conf {int /*<<< orphan*/  smps_mode; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct il_priv* priv; } ;
struct TYPE_10__ {struct ieee80211_channel* chan; } ;
struct ieee80211_channel_switch {TYPE_5__ chandef; } ;
struct ieee80211_channel {scalar_t__ hw_value; int /*<<< orphan*/  band; } ;
struct TYPE_9__ {scalar_t__ (* set_channel_switch ) (struct il_priv*,struct ieee80211_channel_switch*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*) ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_ABOVE ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_BELOW ; 
 int /*<<< orphan*/  IEEE80211_HT_PARAM_CHA_SEC_NONE ; 
#define  NL80211_CHAN_HT20 131 
#define  NL80211_CHAN_HT40MINUS 130 
#define  NL80211_CHAN_HT40PLUS 129 
#define  NL80211_CHAN_NO_HT 128 
 int /*<<< orphan*/  S_CHANNEL_SWITCH_PENDING ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int cfg80211_get_chandef_type (TYPE_5__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_chswitch_done (int /*<<< orphan*/ ,int) ; 
 struct il_channel_info* il_get_channel_info (struct il_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  il_is_associated (struct il_priv*) ; 
 int /*<<< orphan*/  il_is_channel_valid (struct il_channel_info const*) ; 
 scalar_t__ il_is_rfkill (struct il_priv*) ; 
 int /*<<< orphan*/  il_set_flags_for_band (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_set_rate (struct il_priv*) ; 
 int /*<<< orphan*/  il_set_rxon_channel (struct il_priv*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  il_set_rxon_ht (struct il_priv*,struct il_ht_config*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct il_priv*,struct ieee80211_channel_switch*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
il4965_mac_channel_switch(struct ieee80211_hw *hw,
			  struct ieee80211_channel_switch *ch_switch)
{
	struct il_priv *il = hw->priv;
	const struct il_channel_info *ch_info;
	struct ieee80211_conf *conf = &hw->conf;
	struct ieee80211_channel *channel = ch_switch->chandef.chan;
	struct il_ht_config *ht_conf = &il->current_ht_config;
	u16 ch;

	D_MAC80211("enter\n");

	mutex_lock(&il->mutex);

	if (il_is_rfkill(il))
		goto out;

	if (test_bit(S_EXIT_PENDING, &il->status) ||
	    test_bit(S_SCANNING, &il->status) ||
	    test_bit(S_CHANNEL_SWITCH_PENDING, &il->status))
		goto out;

	if (!il_is_associated(il))
		goto out;

	if (!il->ops->set_channel_switch)
		goto out;

	ch = channel->hw_value;
	if (le16_to_cpu(il->active.channel) == ch)
		goto out;

	ch_info = il_get_channel_info(il, channel->band, ch);
	if (!il_is_channel_valid(ch_info)) {
		D_MAC80211("invalid channel\n");
		goto out;
	}

	spin_lock_irq(&il->lock);

	il->current_ht_config.smps = conf->smps_mode;

	/* Configure HT40 channels */
	switch (cfg80211_get_chandef_type(&ch_switch->chandef)) {
	case NL80211_CHAN_NO_HT:
	case NL80211_CHAN_HT20:
		il->ht.is_40mhz = false;
		il->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_NONE;
		break;
	case NL80211_CHAN_HT40MINUS:
		il->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		il->ht.is_40mhz = true;
		break;
	case NL80211_CHAN_HT40PLUS:
		il->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		il->ht.is_40mhz = true;
		break;
	}

	if ((le16_to_cpu(il->staging.channel) != ch))
		il->staging.flags = 0;

	il_set_rxon_channel(il, channel);
	il_set_rxon_ht(il, ht_conf);
	il_set_flags_for_band(il, channel->band, il->vif);

	spin_unlock_irq(&il->lock);

	il_set_rate(il);
	/*
	 * at this point, staging_rxon has the
	 * configuration for channel switch
	 */
	set_bit(S_CHANNEL_SWITCH_PENDING, &il->status);
	il->switch_channel = cpu_to_le16(ch);
	if (il->ops->set_channel_switch(il, ch_switch)) {
		clear_bit(S_CHANNEL_SWITCH_PENDING, &il->status);
		il->switch_channel = 0;
		ieee80211_chswitch_done(il->vif, false);
	}

out:
	mutex_unlock(&il->mutex);
	D_MAC80211("leave\n");
}