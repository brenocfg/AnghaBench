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
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  basic_rate_set; int /*<<< orphan*/  beacon_int; } ;
struct wl1271 {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  beacon_int; } ;

/* Variables and functions */
 int BSS_CHANGED_AP_PROBE_RESP ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_INT ; 
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int /*<<< orphan*/  DEBUG_MASTER ; 
 int /*<<< orphan*/  wl1271_ap_set_probe_resp_tmpl (struct wl1271*,int,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*,int) ; 
 int wl1271_tx_min_rate_get (struct wl1271*,int /*<<< orphan*/ ) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 
 int wlcore_set_beacon_template (struct wl1271*,struct ieee80211_vif*,int) ; 

__attribute__((used)) static int wl1271_bss_beacon_info_changed(struct wl1271 *wl,
					  struct ieee80211_vif *vif,
					  struct ieee80211_bss_conf *bss_conf,
					  u32 changed)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	bool is_ap = (wlvif->bss_type == BSS_TYPE_AP_BSS);
	int ret = 0;

	if (changed & BSS_CHANGED_BEACON_INT) {
		wl1271_debug(DEBUG_MASTER, "beacon interval updated: %d",
			bss_conf->beacon_int);

		wlvif->beacon_int = bss_conf->beacon_int;
	}

	if ((changed & BSS_CHANGED_AP_PROBE_RESP) && is_ap) {
		u32 rate = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);

		wl1271_ap_set_probe_resp_tmpl(wl, rate, vif);
	}

	if (changed & BSS_CHANGED_BEACON) {
		ret = wlcore_set_beacon_template(wl, vif, is_ap);
		if (ret < 0)
			goto out;
	}

out:
	if (ret != 0)
		wl1271_error("beacon info change failed: %d", ret);
	return ret;
}