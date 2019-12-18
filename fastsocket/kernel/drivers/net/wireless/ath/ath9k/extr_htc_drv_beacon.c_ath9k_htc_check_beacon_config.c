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
struct ieee80211_bss_conf {scalar_t__ beacon_int; } ;
struct ieee80211_vif {scalar_t__ type; struct ieee80211_bss_conf bss_conf; } ;
struct htc_beacon_config {scalar_t__ beacon_interval; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_priv {int num_ap_vif; int num_sta_vif; int /*<<< orphan*/  hw; TYPE_1__* ah; struct htc_beacon_config cur_beacon_conf; } ;
struct TYPE_2__ {scalar_t__ opmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ath9k_htc_beacon_iter ; 
 struct ath_common* ath9k_hw_common (TYPE_1__*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool ath9k_htc_check_beacon_config(struct ath9k_htc_priv *priv,
					  struct ieee80211_vif *vif)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct htc_beacon_config *cur_conf = &priv->cur_beacon_conf;
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	bool beacon_configured;

	/*
	 * Changing the beacon interval when multiple AP interfaces
	 * are configured will affect beacon transmission of all
	 * of them.
	 */
	if ((priv->ah->opmode == NL80211_IFTYPE_AP) &&
	    (priv->num_ap_vif > 1) &&
	    (vif->type == NL80211_IFTYPE_AP) &&
	    (cur_conf->beacon_interval != bss_conf->beacon_int)) {
		ath_dbg(common, CONFIG,
			"Changing beacon interval of multiple AP interfaces !\n");
		return false;
	}

	/*
	 * If the HW is operating in AP mode, any new station interfaces that
	 * are added cannot change the beacon parameters.
	 */
	if (priv->num_ap_vif &&
	    (vif->type != NL80211_IFTYPE_AP)) {
		ath_dbg(common, CONFIG,
			"HW in AP mode, cannot set STA beacon parameters\n");
		return false;
	}

	/*
	 * The beacon parameters are configured only for the first
	 * station interface.
	 */
	if ((priv->ah->opmode == NL80211_IFTYPE_STATION) &&
	    (priv->num_sta_vif > 1) &&
	    (vif->type == NL80211_IFTYPE_STATION)) {
		beacon_configured = false;
		ieee80211_iterate_active_interfaces_atomic(
			priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			ath9k_htc_beacon_iter, &beacon_configured);

		if (beacon_configured) {
			ath_dbg(common, CONFIG,
				"Beacon already configured for a station interface\n");
			return false;
		}
	}

	return true;
}