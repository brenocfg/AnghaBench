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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  qos; int /*<<< orphan*/  hlid; } ;
struct wl12xx_vif {scalar_t__ bss_type; size_t band; int /*<<< orphan*/  ip_addr; TYPE_2__ sta; int /*<<< orphan*/  rate_set; int /*<<< orphan*/  flags; int /*<<< orphan*/  basic_rate_set; int /*<<< orphan*/  basic_rate; int /*<<< orphan*/  rssi_thold; } ;
struct TYPE_9__ {scalar_t__ forced_ps; } ;
struct TYPE_10__ {TYPE_4__ conn; } ;
struct wl1271 {TYPE_5__ conf; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_8__ {int* rx_mask; } ;
struct ieee80211_sta_ht_cap {scalar_t__ ht_supported; TYPE_3__ mcs; } ;
struct ieee80211_sta {int* supp_rates; struct ieee80211_sta_ht_cap ht_cap; } ;
struct TYPE_6__ {scalar_t__ width; } ;
struct ieee80211_bss_conf {int basic_rates; int arp_addr_cnt; scalar_t__ assoc; int /*<<< orphan*/  qos; int /*<<< orphan*/ * arp_addr_list; int /*<<< orphan*/  ht_operation_mode; TYPE_1__ chandef; scalar_t__ ps; int /*<<< orphan*/  ibss_joined; int /*<<< orphan*/  bssid; int /*<<< orphan*/  cqm_rssi_thold; int /*<<< orphan*/  cqm_rssi_hyst; scalar_t__ enable_beacon; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ACX_ARP_FILTER_ARP_FILTERING ; 
 int ACX_ARP_FILTER_AUTO_ARP ; 
 int BSS_CHANGED_ARP_FILTER ; 
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_CQM ; 
 int BSS_CHANGED_HT ; 
 int BSS_CHANGED_IBSS ; 
 int BSS_CHANGED_PS ; 
 int BSS_CHANGED_QOS ; 
 scalar_t__ BSS_TYPE_IBSS ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  CONF_TX_IBSS_DEFAULT_RATES ; 
 int /*<<< orphan*/  DEBUG_ADHOC ; 
 int /*<<< orphan*/  DEBUG_PSM ; 
 int HW_HT_RATES_OFFSET ; 
 int HW_MIMO_RATES_OFFSET ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 int STATION_ACTIVE_MODE ; 
 int STATION_AUTO_PS_MODE ; 
 int STATION_POWER_SAVE_MODE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WLVIF_FLAG_IBSS_JOINED ; 
 int /*<<< orphan*/  WLVIF_FLAG_IN_PS ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_ASSOCIATED ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_AUTHORIZED ; 
 struct ieee80211_sta* ieee80211_find_sta (struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_acx_arp_ip_filter (struct wl1271*,struct wl12xx_vif*,int,int /*<<< orphan*/ ) ; 
 int wl1271_acx_rssi_snr_trigger (struct wl1271*,struct wl12xx_vif*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_acx_set_ht_information (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ) ; 
 int wl1271_acx_sta_rate_policies (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_bss_beacon_info_changed (struct wl1271*,struct ieee80211_vif*,struct ieee80211_bss_conf*,int) ; 
 int wl1271_bss_erp_info_changed (struct wl1271*,struct ieee80211_vif*,struct ieee80211_bss_conf*,int) ; 
 int wl1271_cmd_build_arp_rsp (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,...) ; 
 int wl1271_ps_set_mode (struct wl1271*,struct wl12xx_vif*,int) ; 
 int /*<<< orphan*/  wl1271_tx_enabled_rates_get (struct wl1271*,int,size_t) ; 
 int /*<<< orphan*/  wl1271_tx_min_rate_get (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*,...) ; 
 int /*<<< orphan*/  wl12xx_cmd_role_stop_sta (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl12xx_set_authorized (struct wl1271*,struct wl12xx_vif*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 
 int wlcore_clear_bssid (struct wl1271*,struct wl12xx_vif*) ; 
 int wlcore_hw_set_peer_cap (struct wl1271*,struct ieee80211_sta_ht_cap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wlcore_join (struct wl1271*,struct wl12xx_vif*) ; 
 int wlcore_set_assoc (struct wl1271*,struct wl12xx_vif*,struct ieee80211_bss_conf*,int) ; 
 int wlcore_set_bssid (struct wl1271*,struct wl12xx_vif*,struct ieee80211_bss_conf*,int) ; 
 int /*<<< orphan*/  wlcore_unset_assoc (struct wl1271*,struct wl12xx_vif*) ; 

__attribute__((used)) static void wl1271_bss_info_changed_sta(struct wl1271 *wl,
					struct ieee80211_vif *vif,
					struct ieee80211_bss_conf *bss_conf,
					u32 changed)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	bool do_join = false;
	bool is_ibss = (wlvif->bss_type == BSS_TYPE_IBSS);
	bool ibss_joined = false;
	u32 sta_rate_set = 0;
	int ret;
	struct ieee80211_sta *sta;
	bool sta_exists = false;
	struct ieee80211_sta_ht_cap sta_ht_cap;

	if (is_ibss) {
		ret = wl1271_bss_beacon_info_changed(wl, vif, bss_conf,
						     changed);
		if (ret < 0)
			goto out;
	}

	if (changed & BSS_CHANGED_IBSS) {
		if (bss_conf->ibss_joined) {
			set_bit(WLVIF_FLAG_IBSS_JOINED, &wlvif->flags);
			ibss_joined = true;
		} else {
			wlcore_unset_assoc(wl, wlvif);
			wl12xx_cmd_role_stop_sta(wl, wlvif);
		}
	}

	if ((changed & BSS_CHANGED_BEACON_INT) && ibss_joined)
		do_join = true;

	/* Need to update the SSID (for filtering etc) */
	if ((changed & BSS_CHANGED_BEACON) && ibss_joined)
		do_join = true;

	if ((changed & BSS_CHANGED_BEACON_ENABLED) && ibss_joined) {
		wl1271_debug(DEBUG_ADHOC, "ad-hoc beaconing: %s",
			     bss_conf->enable_beacon ? "enabled" : "disabled");

		do_join = true;
	}

	if (changed & BSS_CHANGED_CQM) {
		bool enable = false;
		if (bss_conf->cqm_rssi_thold)
			enable = true;
		ret = wl1271_acx_rssi_snr_trigger(wl, wlvif, enable,
						  bss_conf->cqm_rssi_thold,
						  bss_conf->cqm_rssi_hyst);
		if (ret < 0)
			goto out;
		wlvif->rssi_thold = bss_conf->cqm_rssi_thold;
	}

	if (changed & (BSS_CHANGED_BSSID | BSS_CHANGED_HT |
		       BSS_CHANGED_ASSOC)) {
		rcu_read_lock();
		sta = ieee80211_find_sta(vif, bss_conf->bssid);
		if (sta) {
			u8 *rx_mask = sta->ht_cap.mcs.rx_mask;

			/* save the supp_rates of the ap */
			sta_rate_set = sta->supp_rates[wlvif->band];
			if (sta->ht_cap.ht_supported)
				sta_rate_set |=
					(rx_mask[0] << HW_HT_RATES_OFFSET) |
					(rx_mask[1] << HW_MIMO_RATES_OFFSET);
			sta_ht_cap = sta->ht_cap;
			sta_exists = true;
		}

		rcu_read_unlock();
	}

	if (changed & BSS_CHANGED_BSSID) {
		if (!is_zero_ether_addr(bss_conf->bssid)) {
			ret = wlcore_set_bssid(wl, wlvif, bss_conf,
					       sta_rate_set);
			if (ret < 0)
				goto out;

			/* Need to update the BSSID (for filtering etc) */
			do_join = true;
		} else {
			ret = wlcore_clear_bssid(wl, wlvif);
			if (ret < 0)
				goto out;
		}
	}

	if (changed & BSS_CHANGED_IBSS) {
		wl1271_debug(DEBUG_ADHOC, "ibss_joined: %d",
			     bss_conf->ibss_joined);

		if (bss_conf->ibss_joined) {
			u32 rates = bss_conf->basic_rates;
			wlvif->basic_rate_set =
				wl1271_tx_enabled_rates_get(wl, rates,
							    wlvif->band);
			wlvif->basic_rate =
				wl1271_tx_min_rate_get(wl,
						       wlvif->basic_rate_set);

			/* by default, use 11b + OFDM rates */
			wlvif->rate_set = CONF_TX_IBSS_DEFAULT_RATES;
			ret = wl1271_acx_sta_rate_policies(wl, wlvif);
			if (ret < 0)
				goto out;
		}
	}

	ret = wl1271_bss_erp_info_changed(wl, vif, bss_conf, changed);
	if (ret < 0)
		goto out;

	if (do_join) {
		ret = wlcore_join(wl, wlvif);
		if (ret < 0) {
			wl1271_warning("cmd join failed %d", ret);
			goto out;
		}
	}

	if (changed & BSS_CHANGED_ASSOC) {
		if (bss_conf->assoc) {
			ret = wlcore_set_assoc(wl, wlvif, bss_conf,
					       sta_rate_set);
			if (ret < 0)
				goto out;

			if (test_bit(WLVIF_FLAG_STA_AUTHORIZED, &wlvif->flags))
				wl12xx_set_authorized(wl, wlvif);
		} else {
			wlcore_unset_assoc(wl, wlvif);
		}
	}

	if (changed & BSS_CHANGED_PS) {
		if ((bss_conf->ps) &&
		    test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags) &&
		    !test_bit(WLVIF_FLAG_IN_PS, &wlvif->flags)) {
			int ps_mode;
			char *ps_mode_str;

			if (wl->conf.conn.forced_ps) {
				ps_mode = STATION_POWER_SAVE_MODE;
				ps_mode_str = "forced";
			} else {
				ps_mode = STATION_AUTO_PS_MODE;
				ps_mode_str = "auto";
			}

			wl1271_debug(DEBUG_PSM, "%s ps enabled", ps_mode_str);

			ret = wl1271_ps_set_mode(wl, wlvif, ps_mode);
			if (ret < 0)
				wl1271_warning("enter %s ps failed %d",
					       ps_mode_str, ret);
		} else if (!bss_conf->ps &&
			   test_bit(WLVIF_FLAG_IN_PS, &wlvif->flags)) {
			wl1271_debug(DEBUG_PSM, "auto ps disabled");

			ret = wl1271_ps_set_mode(wl, wlvif,
						 STATION_ACTIVE_MODE);
			if (ret < 0)
				wl1271_warning("exit auto ps failed %d", ret);
		}
	}

	/* Handle new association with HT. Do this after join. */
	if (sta_exists &&
	    (changed & BSS_CHANGED_HT)) {
		bool enabled =
			bss_conf->chandef.width != NL80211_CHAN_WIDTH_20_NOHT;

		ret = wlcore_hw_set_peer_cap(wl,
					     &sta_ht_cap,
					     enabled,
					     wlvif->rate_set,
					     wlvif->sta.hlid);
		if (ret < 0) {
			wl1271_warning("Set ht cap failed %d", ret);
			goto out;

		}

		if (enabled) {
			ret = wl1271_acx_set_ht_information(wl, wlvif,
						bss_conf->ht_operation_mode);
			if (ret < 0) {
				wl1271_warning("Set ht information failed %d",
					       ret);
				goto out;
			}
		}
	}

	/* Handle arp filtering. Done after join. */
	if ((changed & BSS_CHANGED_ARP_FILTER) ||
	    (!is_ibss && (changed & BSS_CHANGED_QOS))) {
		__be32 addr = bss_conf->arp_addr_list[0];
		wlvif->sta.qos = bss_conf->qos;
		WARN_ON(wlvif->bss_type != BSS_TYPE_STA_BSS);

		if (bss_conf->arp_addr_cnt == 1 && bss_conf->assoc) {
			wlvif->ip_addr = addr;
			/*
			 * The template should have been configured only upon
			 * association. however, it seems that the correct ip
			 * isn't being set (when sending), so we have to
			 * reconfigure the template upon every ip change.
			 */
			ret = wl1271_cmd_build_arp_rsp(wl, wlvif);
			if (ret < 0) {
				wl1271_warning("build arp rsp failed: %d", ret);
				goto out;
			}

			ret = wl1271_acx_arp_ip_filter(wl, wlvif,
				(ACX_ARP_FILTER_ARP_FILTERING |
				 ACX_ARP_FILTER_AUTO_ARP),
				addr);
		} else {
			wlvif->ip_addr = 0;
			ret = wl1271_acx_arp_ip_filter(wl, wlvif, 0, addr);
		}

		if (ret < 0)
			goto out;
	}

out:
	return;
}