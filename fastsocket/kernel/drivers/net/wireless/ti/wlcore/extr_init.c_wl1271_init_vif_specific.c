#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wl12xx_vif {scalar_t__ bss_type; } ;
struct TYPE_5__ {int tid_conf_count; int ac_conf_count; struct conf_tx_tid* tid_conf; struct conf_tx_ac_category* ac_conf; } ;
struct TYPE_4__ {scalar_t__ sta_sleep_auth; } ;
struct TYPE_6__ {TYPE_2__ tx; TYPE_1__ conn; } ;
struct wl1271 {scalar_t__ ap_count; scalar_t__ sta_count; TYPE_3__ conf; } ;
struct ieee80211_vif {int dummy; } ;
struct conf_tx_tid {int /*<<< orphan*/ * apsd_conf; int /*<<< orphan*/  ack_policy; int /*<<< orphan*/  ps_scheme; int /*<<< orphan*/  tsid; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  queue_id; } ;
struct conf_tx_ac_category {int /*<<< orphan*/  tx_op_limit; int /*<<< orphan*/  aifsn; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; int /*<<< orphan*/  ac; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ WL1271_PSM_CAM ; 
 scalar_t__ WL1271_PSM_ELP ; 
 scalar_t__ WL1271_PSM_ILLEGAL ; 
 int wl1271_acx_ac_cfg (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_acx_feature_cfg (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_acx_sleep_auth (struct wl1271*,scalar_t__) ; 
 int wl1271_acx_tid_cfg (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_ap_hw_init (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_ap_hw_init_post_mem (struct wl1271*,struct ieee80211_vif*) ; 
 int wl1271_set_ba_policies (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_sta_hw_init (struct wl1271*,struct wl12xx_vif*) ; 
 int wl1271_sta_hw_init_post_mem (struct wl1271*,struct ieee80211_vif*) ; 
 int wl12xx_init_ap_role (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl12xx_init_phy_vif_config (struct wl1271*,struct wl12xx_vif*) ; 
 int wl12xx_init_sta_role (struct wl1271*,struct wl12xx_vif*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 
 int wlcore_hw_init_vif (struct wl1271*,struct wl12xx_vif*) ; 

int wl1271_init_vif_specific(struct wl1271 *wl, struct ieee80211_vif *vif)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct conf_tx_ac_category *conf_ac;
	struct conf_tx_tid *conf_tid;
	bool is_ap = (wlvif->bss_type == BSS_TYPE_AP_BSS);
	int ret, i;

	/* consider all existing roles before configuring psm. */

	if (wl->ap_count == 0 && is_ap) { /* first AP */
		/* Configure for power always on */
		ret = wl1271_acx_sleep_auth(wl, WL1271_PSM_CAM);
		if (ret < 0)
			return ret;
	/* first STA, no APs */
	} else if (wl->sta_count == 0 && wl->ap_count == 0 && !is_ap) {
		u8 sta_auth = wl->conf.conn.sta_sleep_auth;
		/* Configure for power according to debugfs */
		if (sta_auth != WL1271_PSM_ILLEGAL)
			ret = wl1271_acx_sleep_auth(wl, sta_auth);
		/* Configure for ELP power saving */
		else
			ret = wl1271_acx_sleep_auth(wl, WL1271_PSM_ELP);

		if (ret < 0)
			return ret;
	}

	/* Mode specific init */
	if (is_ap) {
		ret = wl1271_ap_hw_init(wl, wlvif);
		if (ret < 0)
			return ret;

		ret = wl12xx_init_ap_role(wl, wlvif);
		if (ret < 0)
			return ret;
	} else {
		ret = wl1271_sta_hw_init(wl, wlvif);
		if (ret < 0)
			return ret;

		ret = wl12xx_init_sta_role(wl, wlvif);
		if (ret < 0)
			return ret;
	}

	wl12xx_init_phy_vif_config(wl, wlvif);

	/* Default TID/AC configuration */
	BUG_ON(wl->conf.tx.tid_conf_count != wl->conf.tx.ac_conf_count);
	for (i = 0; i < wl->conf.tx.tid_conf_count; i++) {
		conf_ac = &wl->conf.tx.ac_conf[i];
		ret = wl1271_acx_ac_cfg(wl, wlvif, conf_ac->ac,
					conf_ac->cw_min, conf_ac->cw_max,
					conf_ac->aifsn, conf_ac->tx_op_limit);
		if (ret < 0)
			return ret;

		conf_tid = &wl->conf.tx.tid_conf[i];
		ret = wl1271_acx_tid_cfg(wl, wlvif,
					 conf_tid->queue_id,
					 conf_tid->channel_type,
					 conf_tid->tsid,
					 conf_tid->ps_scheme,
					 conf_tid->ack_policy,
					 conf_tid->apsd_conf[0],
					 conf_tid->apsd_conf[1]);
		if (ret < 0)
			return ret;
	}

	/* Configure HW encryption */
	ret = wl1271_acx_feature_cfg(wl, wlvif);
	if (ret < 0)
		return ret;

	/* Mode specific init - post mem init */
	if (is_ap)
		ret = wl1271_ap_hw_init_post_mem(wl, vif);
	else
		ret = wl1271_sta_hw_init_post_mem(wl, vif);

	if (ret < 0)
		return ret;

	/* Configure initiator BA sessions policies */
	ret = wl1271_set_ba_policies(wl, wlvif);
	if (ret < 0)
		return ret;

	ret = wlcore_hw_init_vif(wl, wlvif);
	if (ret < 0)
		return ret;

	return 0;
}