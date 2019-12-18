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
typedef  int u32 ;
struct mwl8k_priv {scalar_t__ ap_fw; } ;
struct ieee80211_conf {int flags; int power_level; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; struct ieee80211_conf conf; } ;

/* Variables and functions */
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_POWER ; 
 int IEEE80211_CONF_IDLE ; 
 int mwl8k_cmd_mimo_config (struct ieee80211_hw*,int,int) ; 
 int mwl8k_cmd_radio_disable (struct ieee80211_hw*) ; 
 int mwl8k_cmd_radio_enable (struct ieee80211_hw*) ; 
 int mwl8k_cmd_rf_tx_power (struct ieee80211_hw*,int) ; 
 int mwl8k_cmd_set_rf_channel (struct ieee80211_hw*,struct ieee80211_conf*) ; 
 int mwl8k_cmd_tx_power (struct ieee80211_hw*,struct ieee80211_conf*,int) ; 
 int mwl8k_fw_lock (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_fw_unlock (struct ieee80211_hw*) ; 

__attribute__((used)) static int mwl8k_config(struct ieee80211_hw *hw, u32 changed)
{
	struct ieee80211_conf *conf = &hw->conf;
	struct mwl8k_priv *priv = hw->priv;
	int rc;

	rc = mwl8k_fw_lock(hw);
	if (rc)
		return rc;

	if (conf->flags & IEEE80211_CONF_IDLE)
		rc = mwl8k_cmd_radio_disable(hw);
	else
		rc = mwl8k_cmd_radio_enable(hw);
	if (rc)
		goto out;

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		rc = mwl8k_cmd_set_rf_channel(hw, conf);
		if (rc)
			goto out;
	}

	if (conf->power_level > 18)
		conf->power_level = 18;

	if (priv->ap_fw) {

		if (conf->flags & IEEE80211_CONF_CHANGE_POWER) {
			rc = mwl8k_cmd_tx_power(hw, conf, conf->power_level);
			if (rc)
				goto out;
		}


	} else {
		rc = mwl8k_cmd_rf_tx_power(hw, conf->power_level);
		if (rc)
			goto out;
		rc = mwl8k_cmd_mimo_config(hw, 0x7, 0x7);
	}

out:
	mwl8k_fw_unlock(hw);

	return rc;
}