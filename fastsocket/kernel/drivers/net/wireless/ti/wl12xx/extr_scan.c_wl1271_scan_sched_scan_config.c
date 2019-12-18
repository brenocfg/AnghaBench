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
typedef  size_t u8 ;
struct wlcore_scan_channels {int report_after; int filter_type; scalar_t__* active; scalar_t__ ssid_len; int /*<<< orphan*/ * intervals; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  tag; scalar_t__ terminate; scalar_t__ cycles; int /*<<< orphan*/  n_probe_reqs; int /*<<< orphan*/  snr_threshold; int /*<<< orphan*/  rssi_threshold; int /*<<< orphan*/  role_id; } ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271_cmd_sched_scan_config {int report_after; int filter_type; scalar_t__* active; scalar_t__ ssid_len; int /*<<< orphan*/ * intervals; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  tag; scalar_t__ terminate; scalar_t__ cycles; int /*<<< orphan*/  n_probe_reqs; int /*<<< orphan*/  snr_threshold; int /*<<< orphan*/  rssi_threshold; int /*<<< orphan*/  role_id; } ;
struct conf_sched_scan_settings {int /*<<< orphan*/  num_probe_reqs; int /*<<< orphan*/  snr_threshold; int /*<<< orphan*/  rssi_threshold; } ;
struct TYPE_3__ {struct conf_sched_scan_settings sched_scan; } ;
struct wl1271 {TYPE_1__ conf; } ;
struct ieee80211_sched_scan_ies {int /*<<< orphan*/ * len; int /*<<< orphan*/ * ie; } ;
struct cfg80211_sched_scan_request {TYPE_2__* ssids; int /*<<< orphan*/  n_ssids; int /*<<< orphan*/  n_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  interval; } ;
struct TYPE_4__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CONNECTION_SCAN_CFG ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  DEBUG_SCAN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IEEE80211_BAND_2GHZ ; 
 size_t IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  SCAN_BSS_TYPE_ANY ; 
 int SCAN_MAX_CYCLE_INTERVALS ; 
 int /*<<< orphan*/  SCAN_TYPE_PERIODIC ; 
 int /*<<< orphan*/  WL1271_SCAN_DEFAULT_TAG ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wlcore_scan_channels*) ; 
 struct wlcore_scan_channels* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wlcore_scan_channels*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wl1271_dump (int /*<<< orphan*/ ,char*,struct wlcore_scan_channels*,int) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int /*<<< orphan*/  wl12xx_adjust_channels (struct wlcore_scan_channels*,struct wlcore_scan_channels*) ; 
 int wl12xx_cmd_build_probe_req (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wlcore_scan_sched_scan_ssid_list (struct wl1271*,struct wl12xx_vif*,struct cfg80211_sched_scan_request*) ; 
 int /*<<< orphan*/  wlcore_set_scan_chan_params (struct wl1271*,struct wlcore_scan_channels*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wl1271_scan_sched_scan_config(struct wl1271 *wl,
				  struct wl12xx_vif *wlvif,
				  struct cfg80211_sched_scan_request *req,
				  struct ieee80211_sched_scan_ies *ies)
{
	struct wl1271_cmd_sched_scan_config *cfg = NULL;
	struct wlcore_scan_channels *cfg_channels = NULL;
	struct conf_sched_scan_settings *c = &wl->conf.sched_scan;
	int i, ret;
	bool force_passive = !req->n_ssids;

	wl1271_debug(DEBUG_CMD, "cmd sched_scan scan config");

	cfg = kzalloc(sizeof(*cfg), GFP_KERNEL);
	if (!cfg)
		return -ENOMEM;

	cfg->role_id = wlvif->role_id;
	cfg->rssi_threshold = c->rssi_threshold;
	cfg->snr_threshold  = c->snr_threshold;
	cfg->n_probe_reqs = c->num_probe_reqs;
	/* cycles set to 0 it means infinite (until manually stopped) */
	cfg->cycles = 0;
	/* report APs when at least 1 is found */
	cfg->report_after = 1;
	/* don't stop scanning automatically when something is found */
	cfg->terminate = 0;
	cfg->tag = WL1271_SCAN_DEFAULT_TAG;
	/* don't filter on BSS type */
	cfg->bss_type = SCAN_BSS_TYPE_ANY;
	/* currently NL80211 supports only a single interval */
	for (i = 0; i < SCAN_MAX_CYCLE_INTERVALS; i++)
		cfg->intervals[i] = cpu_to_le32(req->interval);

	cfg->ssid_len = 0;
	ret = wlcore_scan_sched_scan_ssid_list(wl, wlvif, req);
	if (ret < 0)
		goto out;

	cfg->filter_type = ret;

	wl1271_debug(DEBUG_SCAN, "filter_type = %d", cfg->filter_type);

	cfg_channels = kzalloc(sizeof(*cfg_channels), GFP_KERNEL);
	if (!cfg_channels) {
		ret = -ENOMEM;
		goto out;
	}

	if (!wlcore_set_scan_chan_params(wl, cfg_channels, req->channels,
					 req->n_channels, req->n_ssids,
					 SCAN_TYPE_PERIODIC)) {
		wl1271_error("scan channel list is empty");
		ret = -EINVAL;
		goto out;
	}
	wl12xx_adjust_channels(cfg, cfg_channels);

	if (!force_passive && cfg->active[0]) {
		u8 band = IEEE80211_BAND_2GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvif,
						 wlvif->role_id, band,
						 req->ssids[0].ssid,
						 req->ssids[0].ssid_len,
						 ies->ie[band],
						 ies->len[band], true);
		if (ret < 0) {
			wl1271_error("2.4GHz PROBE request template failed");
			goto out;
		}
	}

	if (!force_passive && cfg->active[1]) {
		u8 band = IEEE80211_BAND_5GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvif,
						 wlvif->role_id, band,
						 req->ssids[0].ssid,
						 req->ssids[0].ssid_len,
						 ies->ie[band],
						 ies->len[band], true);
		if (ret < 0) {
			wl1271_error("5GHz PROBE request template failed");
			goto out;
		}
	}

	wl1271_dump(DEBUG_SCAN, "SCAN_CFG: ", cfg, sizeof(*cfg));

	ret = wl1271_cmd_send(wl, CMD_CONNECTION_SCAN_CFG, cfg,
			      sizeof(*cfg), 0);
	if (ret < 0) {
		wl1271_error("SCAN configuration failed");
		goto out;
	}
out:
	kfree(cfg_channels);
	kfree(cfg);
	return ret;
}