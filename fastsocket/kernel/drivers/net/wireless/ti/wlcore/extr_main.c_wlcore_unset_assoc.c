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
struct TYPE_2__ {int /*<<< orphan*/  klv_template_id; } ;
struct wl12xx_vif {scalar_t__ bss_type; TYPE_1__ sta; int /*<<< orphan*/  channel_switch_work; int /*<<< orphan*/  flags; int /*<<< orphan*/ * probereq; scalar_t__ aid; } ;
struct wl1271 {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_KEEP_ALIVE_TPL_INVALID ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  WLVIF_FLAG_CS_PROGRESS ; 
 int /*<<< orphan*/  WLVIF_FLAG_IBSS_JOINED ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_ASSOCIATED ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_chswitch_done (struct ieee80211_vif*,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_acx_conn_monit_params (struct wl1271*,struct wl12xx_vif*,int) ; 
 int /*<<< orphan*/  wl1271_acx_keep_alive_config (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_acx_keep_alive_mode (struct wl1271*,struct wl12xx_vif*,int) ; 
 int /*<<< orphan*/  wl12xx_cmd_stop_channel_switch (struct wl1271*,struct wl12xx_vif*) ; 
 struct ieee80211_vif* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 

__attribute__((used)) static int wlcore_unset_assoc(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;
	bool sta = wlvif->bss_type == BSS_TYPE_STA_BSS;

	/* make sure we are connected (sta) joined */
	if (sta &&
	    !test_and_clear_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags))
		return false;

	/* make sure we are joined (ibss) */
	if (!sta &&
	    test_and_clear_bit(WLVIF_FLAG_IBSS_JOINED, &wlvif->flags))
		return false;

	if (sta) {
		/* use defaults when not associated */
		wlvif->aid = 0;

		/* free probe-request template */
		dev_kfree_skb(wlvif->probereq);
		wlvif->probereq = NULL;

		/* disable connection monitor features */
		ret = wl1271_acx_conn_monit_params(wl, wlvif, false);
		if (ret < 0)
			return ret;

		/* Disable the keep-alive feature */
		ret = wl1271_acx_keep_alive_mode(wl, wlvif, false);
		if (ret < 0)
			return ret;
	}

	if (test_and_clear_bit(WLVIF_FLAG_CS_PROGRESS, &wlvif->flags)) {
		struct ieee80211_vif *vif = wl12xx_wlvif_to_vif(wlvif);

		wl12xx_cmd_stop_channel_switch(wl, wlvif);
		ieee80211_chswitch_done(vif, false);
		cancel_delayed_work(&wlvif->channel_switch_work);
	}

	/* invalidate keep-alive template */
	wl1271_acx_keep_alive_config(wl, wlvif,
				     wlvif->sta.klv_template_id,
				     ACX_KEEP_ALIVE_TPL_INVALID);

	return 0;
}