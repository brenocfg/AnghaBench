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
struct wl12xx_vif {scalar_t__ bss_type; scalar_t__ role_id; int /*<<< orphan*/  channel; int /*<<< orphan*/  band; int /*<<< orphan*/  flags; } ;
struct wl1271_station {int /*<<< orphan*/  hlid; } ;
struct wl1271 {int /*<<< orphan*/  roc_map; } ;
struct ieee80211_sta {int /*<<< orphan*/  ht_cap; scalar_t__ drv_priv; } ;
typedef  enum ieee80211_sta_state { ____Placeholder_ieee80211_sta_state } ieee80211_sta_state ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int IEEE80211_STA_ASSOC ; 
 int IEEE80211_STA_AUTHORIZED ; 
 int IEEE80211_STA_NONE ; 
 int IEEE80211_STA_NOTEXIST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WL12XX_INVALID_ROLE_ID ; 
 scalar_t__ WL12XX_MAX_ROLES ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_AUTHORIZED ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_STATE_SENT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int wl1271_acx_set_ht_capabilities (struct wl1271*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int wl12xx_cmd_set_peer_state (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl12xx_croc (struct wl1271*,scalar_t__) ; 
 int /*<<< orphan*/  wl12xx_roc (struct wl1271*,struct wl12xx_vif*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl12xx_set_authorized (struct wl1271*,struct wl12xx_vif*) ; 
 int wl12xx_sta_add (struct wl1271*,struct wl12xx_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  wl12xx_sta_remove (struct wl1271*,struct wl12xx_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  wlcore_update_inconn_sta (struct wl1271*,struct wl12xx_vif*,struct wl1271_station*,int) ; 

__attribute__((used)) static int wl12xx_update_sta_state(struct wl1271 *wl,
				   struct wl12xx_vif *wlvif,
				   struct ieee80211_sta *sta,
				   enum ieee80211_sta_state old_state,
				   enum ieee80211_sta_state new_state)
{
	struct wl1271_station *wl_sta;
	bool is_ap = wlvif->bss_type == BSS_TYPE_AP_BSS;
	bool is_sta = wlvif->bss_type == BSS_TYPE_STA_BSS;
	int ret;

	wl_sta = (struct wl1271_station *)sta->drv_priv;

	/* Add station (AP mode) */
	if (is_ap &&
	    old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) {
		ret = wl12xx_sta_add(wl, wlvif, sta);
		if (ret)
			return ret;

		wlcore_update_inconn_sta(wl, wlvif, wl_sta, true);
	}

	/* Remove station (AP mode) */
	if (is_ap &&
	    old_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST) {
		/* must not fail */
		wl12xx_sta_remove(wl, wlvif, sta);

		wlcore_update_inconn_sta(wl, wlvif, wl_sta, false);
	}

	/* Authorize station (AP mode) */
	if (is_ap &&
	    new_state == IEEE80211_STA_AUTHORIZED) {
		ret = wl12xx_cmd_set_peer_state(wl, wlvif, wl_sta->hlid);
		if (ret < 0)
			return ret;

		ret = wl1271_acx_set_ht_capabilities(wl, &sta->ht_cap, true,
						     wl_sta->hlid);
		if (ret)
			return ret;

		wlcore_update_inconn_sta(wl, wlvif, wl_sta, false);
	}

	/* Authorize station */
	if (is_sta &&
	    new_state == IEEE80211_STA_AUTHORIZED) {
		set_bit(WLVIF_FLAG_STA_AUTHORIZED, &wlvif->flags);
		ret = wl12xx_set_authorized(wl, wlvif);
		if (ret)
			return ret;
	}

	if (is_sta &&
	    old_state == IEEE80211_STA_AUTHORIZED &&
	    new_state == IEEE80211_STA_ASSOC) {
		clear_bit(WLVIF_FLAG_STA_AUTHORIZED, &wlvif->flags);
		clear_bit(WLVIF_FLAG_STA_STATE_SENT, &wlvif->flags);
	}

	/* clear ROCs on failure or authorization */
	if (is_sta &&
	    (new_state == IEEE80211_STA_AUTHORIZED ||
	     new_state == IEEE80211_STA_NOTEXIST)) {
		if (test_bit(wlvif->role_id, wl->roc_map))
			wl12xx_croc(wl, wlvif->role_id);
	}

	if (is_sta &&
	    old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) {
		if (find_first_bit(wl->roc_map,
				   WL12XX_MAX_ROLES) >= WL12XX_MAX_ROLES) {
			WARN_ON(wlvif->role_id == WL12XX_INVALID_ROLE_ID);
			wl12xx_roc(wl, wlvif, wlvif->role_id,
				   wlvif->band, wlvif->channel);
		}
	}
	return 0;
}