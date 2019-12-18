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
typedef  int u32 ;
struct TYPE_10__ {size_t global_hlid; size_t bcast_hlid; } ;
struct wl12xx_vif {int role_id; int basic_rate_set; int band; TYPE_5__ ap; scalar_t__ p2p; scalar_t__ ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  channel; int /*<<< orphan*/  wmm_enabled; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  total_freed_pkts; } ;
struct TYPE_9__ {size_t global_hlid; size_t broadcast_hlid; int reset_tsf; void* local_rates; int /*<<< orphan*/  ssid; scalar_t__ ssid_len; int /*<<< orphan*/  ssid_type; int /*<<< orphan*/  wmm; int /*<<< orphan*/  beacon_expiry; int /*<<< orphan*/  dtim_interval; void* beacon_interval; void* basic_rate_set; int /*<<< orphan*/  bcast_session_id; int /*<<< orphan*/  global_session_id; int /*<<< orphan*/  bss_index; void* aging_period; } ;
struct wl12xx_cmd_role_start {int role_id; void* band; TYPE_4__ ap; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {int /*<<< orphan*/  ap_aging_period; } ;
struct TYPE_8__ {TYPE_2__ tx; } ;
struct wl1271 {int /*<<< orphan*/ * session_ids; TYPE_3__ conf; TYPE_1__* links; } ;
struct ieee80211_bss_conf {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  hidden_ssid; int /*<<< orphan*/  dtim_period; } ;
struct ieee80211_vif {struct ieee80211_bss_conf bss_conf; } ;
struct TYPE_6__ {int /*<<< orphan*/  total_freed_pkts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ROLE_START ; 
 int CONF_TX_CCK_RATES ; 
 int CONF_TX_ENABLED_RATES ; 
 int CONF_TX_MCS_RATES ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 int /*<<< orphan*/  WL1271_AP_BSS_INDEX ; 
 int /*<<< orphan*/  WL1271_AP_DEF_BEACON_EXP ; 
 int /*<<< orphan*/  WL12XX_SSID_TYPE_HIDDEN ; 
 int /*<<< orphan*/  WL12XX_SSID_TYPE_PUBLIC ; 
 void* WLCORE_BAND_2_4GHZ ; 
 void* WLCORE_BAND_5GHZ ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_role_start*) ; 
 struct wl12xx_cmd_role_start* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_role_start*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 
 int wl12xx_allocate_link (struct wl1271*,struct wl12xx_vif*,size_t*) ; 
 int /*<<< orphan*/  wl12xx_free_link (struct wl1271*,struct wl12xx_vif*,size_t*) ; 
 struct ieee80211_vif* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wlcore_get_native_channel_type (int /*<<< orphan*/ ) ; 
 int wlcore_hw_ap_get_mimo_wide_rate_mask (struct wl1271*,struct wl12xx_vif*) ; 

int wl12xx_cmd_role_start_ap(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct wl12xx_cmd_role_start *cmd;
	struct ieee80211_vif *vif = wl12xx_wlvif_to_vif(wlvif);
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	u32 supported_rates;
	int ret;

	wl1271_debug(DEBUG_CMD, "cmd role start ap %d", wlvif->role_id);

	/* trying to use hidden SSID with an old hostapd version */
	if (wlvif->ssid_len == 0 && !bss_conf->hidden_ssid) {
		wl1271_error("got a null SSID from beacon/bss");
		ret = -EINVAL;
		goto out;
	}

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	ret = wl12xx_allocate_link(wl, wlvif, &wlvif->ap.global_hlid);
	if (ret < 0)
		goto out_free;

	ret = wl12xx_allocate_link(wl, wlvif, &wlvif->ap.bcast_hlid);
	if (ret < 0)
		goto out_free_global;

	/* use the previous security seq, if this is a recovery/resume */
	wl->links[wlvif->ap.bcast_hlid].total_freed_pkts =
						wlvif->total_freed_pkts;

	cmd->role_id = wlvif->role_id;
	cmd->ap.aging_period = cpu_to_le16(wl->conf.tx.ap_aging_period);
	cmd->ap.bss_index = WL1271_AP_BSS_INDEX;
	cmd->ap.global_hlid = wlvif->ap.global_hlid;
	cmd->ap.broadcast_hlid = wlvif->ap.bcast_hlid;
	cmd->ap.global_session_id = wl->session_ids[wlvif->ap.global_hlid];
	cmd->ap.bcast_session_id = wl->session_ids[wlvif->ap.bcast_hlid];
	cmd->ap.basic_rate_set = cpu_to_le32(wlvif->basic_rate_set);
	cmd->ap.beacon_interval = cpu_to_le16(wlvif->beacon_int);
	cmd->ap.dtim_interval = bss_conf->dtim_period;
	cmd->ap.beacon_expiry = WL1271_AP_DEF_BEACON_EXP;
	/* FIXME: Change when adding DFS */
	cmd->ap.reset_tsf = 1;  /* By default reset AP TSF */
	cmd->ap.wmm = wlvif->wmm_enabled;
	cmd->channel = wlvif->channel;
	cmd->channel_type = wlcore_get_native_channel_type(wlvif->channel_type);

	if (!bss_conf->hidden_ssid) {
		/* take the SSID from the beacon for backward compatibility */
		cmd->ap.ssid_type = WL12XX_SSID_TYPE_PUBLIC;
		cmd->ap.ssid_len = wlvif->ssid_len;
		memcpy(cmd->ap.ssid, wlvif->ssid, wlvif->ssid_len);
	} else {
		cmd->ap.ssid_type = WL12XX_SSID_TYPE_HIDDEN;
		cmd->ap.ssid_len = bss_conf->ssid_len;
		memcpy(cmd->ap.ssid, bss_conf->ssid, bss_conf->ssid_len);
	}

	supported_rates = CONF_TX_ENABLED_RATES | CONF_TX_MCS_RATES |
		wlcore_hw_ap_get_mimo_wide_rate_mask(wl, wlvif);
	if (wlvif->p2p)
		supported_rates &= ~CONF_TX_CCK_RATES;

	wl1271_debug(DEBUG_CMD, "cmd role start ap with supported_rates 0x%08x",
		     supported_rates);

	cmd->ap.local_rates = cpu_to_le32(supported_rates);

	switch (wlvif->band) {
	case IEEE80211_BAND_2GHZ:
		cmd->band = WLCORE_BAND_2_4GHZ;
		break;
	case IEEE80211_BAND_5GHZ:
		cmd->band = WLCORE_BAND_5GHZ;
		break;
	default:
		wl1271_warning("ap start - unknown band: %d", (int)wlvif->band);
		cmd->band = WLCORE_BAND_2_4GHZ;
		break;
	}

	ret = wl1271_cmd_send(wl, CMD_ROLE_START, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to initiate cmd role start ap");
		goto out_free_bcast;
	}

	goto out_free;

out_free_bcast:
	wl12xx_free_link(wl, wlvif, &wlvif->ap.bcast_hlid);

out_free_global:
	wl12xx_free_link(wl, wlvif, &wlvif->ap.global_hlid);

out_free:
	kfree(cmd);

out:
	return ret;
}