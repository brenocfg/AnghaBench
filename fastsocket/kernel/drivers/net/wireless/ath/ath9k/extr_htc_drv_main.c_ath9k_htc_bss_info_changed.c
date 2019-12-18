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
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ieee80211_bss_conf {scalar_t__ use_short_slot; scalar_t__ bssid; scalar_t__ enable_beacon; int /*<<< orphan*/  aid; scalar_t__ assoc; } ;
struct ath_hw {scalar_t__ opmode; int slottime; } ;
struct ath_common {int /*<<< orphan*/  curbssid; int /*<<< orphan*/  curaid; } ;
struct ath9k_htc_priv {int num_sta_assoc_vif; int num_ap_vif; int nvifs; int /*<<< orphan*/  mutex; int /*<<< orphan*/  op_flags; struct ath_hw* ah; scalar_t__ num_ibss_vif; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_HT ; 
 int BSS_CHANGED_IBSS ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  OP_ENABLE_BEACON ; 
 int /*<<< orphan*/  OP_TSF_RESET ; 
 int /*<<< orphan*/  ath9k_htc_beacon_config (struct ath9k_htc_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_htc_choose_set_bssid (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_set_bssid (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_set_tsfadjust (struct ath9k_htc_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_htc_start_ani (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_stop_ani (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_update_rate (struct ath9k_htc_priv*,struct ieee80211_vif*,struct ieee80211_bss_conf*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_global_settings (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_htc_bss_info_changed(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif,
				       struct ieee80211_bss_conf *bss_conf,
				       u32 changed)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_hw *ah = priv->ah;
	struct ath_common *common = ath9k_hw_common(ah);

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	if (changed & BSS_CHANGED_ASSOC) {
		ath_dbg(common, CONFIG, "BSS Changed ASSOC %d\n",
			bss_conf->assoc);

		bss_conf->assoc ?
			priv->num_sta_assoc_vif++ : priv->num_sta_assoc_vif--;

		if (priv->ah->opmode == NL80211_IFTYPE_STATION) {
			ath9k_htc_choose_set_bssid(priv);
			if (bss_conf->assoc && (priv->num_sta_assoc_vif == 1))
				ath9k_htc_start_ani(priv);
			else if (priv->num_sta_assoc_vif == 0)
				ath9k_htc_stop_ani(priv);
		}
	}

	if (changed & BSS_CHANGED_IBSS) {
		if (priv->ah->opmode == NL80211_IFTYPE_ADHOC) {
			common->curaid = bss_conf->aid;
			memcpy(common->curbssid, bss_conf->bssid, ETH_ALEN);
			ath9k_htc_set_bssid(priv);
		}
	}

	if ((changed & BSS_CHANGED_BEACON_ENABLED) && bss_conf->enable_beacon) {
		ath_dbg(common, CONFIG, "Beacon enabled for BSS: %pM\n",
			bss_conf->bssid);
		ath9k_htc_set_tsfadjust(priv, vif);
		set_bit(OP_ENABLE_BEACON, &priv->op_flags);
		ath9k_htc_beacon_config(priv, vif);
	}

	if ((changed & BSS_CHANGED_BEACON_ENABLED) && !bss_conf->enable_beacon) {
		/*
		 * Disable SWBA interrupt only if there are no
		 * AP/IBSS interfaces.
		 */
		if ((priv->num_ap_vif <= 1) || priv->num_ibss_vif) {
			ath_dbg(common, CONFIG,
				"Beacon disabled for BSS: %pM\n",
				bss_conf->bssid);
			clear_bit(OP_ENABLE_BEACON, &priv->op_flags);
			ath9k_htc_beacon_config(priv, vif);
		}
	}

	if (changed & BSS_CHANGED_BEACON_INT) {
		/*
		 * Reset the HW TSF for the first AP interface.
		 */
		if ((priv->ah->opmode == NL80211_IFTYPE_AP) &&
		    (priv->nvifs == 1) &&
		    (priv->num_ap_vif == 1) &&
		    (vif->type == NL80211_IFTYPE_AP)) {
			set_bit(OP_TSF_RESET, &priv->op_flags);
		}
		ath_dbg(common, CONFIG,
			"Beacon interval changed for BSS: %pM\n",
			bss_conf->bssid);
		ath9k_htc_beacon_config(priv, vif);
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		if (bss_conf->use_short_slot)
			ah->slottime = 9;
		else
			ah->slottime = 20;

		ath9k_hw_init_global_settings(ah);
	}

	if (changed & BSS_CHANGED_HT)
		ath9k_htc_update_rate(priv, vif, bss_conf);

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
}