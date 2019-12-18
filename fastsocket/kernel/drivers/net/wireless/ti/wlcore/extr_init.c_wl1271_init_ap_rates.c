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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * ucast_rate_idx; int /*<<< orphan*/  bcast_rate_idx; int /*<<< orphan*/  mgmt_rate_idx; } ;
struct wl12xx_vif {int basic_rate_set; TYPE_3__ ap; } ;
struct TYPE_4__ {int ac_conf_count; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;
struct wl1271 {TYPE_2__ conf; } ;
struct conf_tx_rate_class {int enabled_rates; int long_retry_limit; int short_retry_limit; scalar_t__ aflags; } ;

/* Variables and functions */
 int CONF_TX_ENABLED_RATES ; 
 int CONF_TX_MCS_RATES ; 
 int CONF_TX_OFDM_RATES ; 
 int /*<<< orphan*/  DEBUG_AP ; 
 int EINVAL ; 
 int wl1271_acx_ap_rate_policy (struct wl1271*,struct conf_tx_rate_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int wl1271_tx_min_rate_get (struct wl1271*,int) ; 
 int wlcore_hw_ap_get_mimo_wide_rate_mask (struct wl1271*,struct wl12xx_vif*) ; 

int wl1271_init_ap_rates(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int i, ret;
	struct conf_tx_rate_class rc;
	u32 supported_rates;

	wl1271_debug(DEBUG_AP, "AP basic rate set: 0x%x",
		     wlvif->basic_rate_set);

	if (wlvif->basic_rate_set == 0)
		return -EINVAL;

	rc.enabled_rates = wlvif->basic_rate_set;
	rc.long_retry_limit = 10;
	rc.short_retry_limit = 10;
	rc.aflags = 0;
	ret = wl1271_acx_ap_rate_policy(wl, &rc, wlvif->ap.mgmt_rate_idx);
	if (ret < 0)
		return ret;

	/* use the min basic rate for AP broadcast/multicast */
	rc.enabled_rates = wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
	rc.short_retry_limit = 10;
	rc.long_retry_limit = 10;
	rc.aflags = 0;
	ret = wl1271_acx_ap_rate_policy(wl, &rc, wlvif->ap.bcast_rate_idx);
	if (ret < 0)
		return ret;

	/*
	 * If the basic rates contain OFDM rates, use OFDM only
	 * rates for unicast TX as well. Else use all supported rates.
	 */
	if ((wlvif->basic_rate_set & CONF_TX_OFDM_RATES))
		supported_rates = CONF_TX_OFDM_RATES;
	else
		supported_rates = CONF_TX_ENABLED_RATES;

	/* unconditionally enable HT rates */
	supported_rates |= CONF_TX_MCS_RATES;

	/* get extra MIMO or wide-chan rates where the HW supports it */
	supported_rates |= wlcore_hw_ap_get_mimo_wide_rate_mask(wl, wlvif);

	/* configure unicast TX rate classes */
	for (i = 0; i < wl->conf.tx.ac_conf_count; i++) {
		rc.enabled_rates = supported_rates;
		rc.short_retry_limit = 10;
		rc.long_retry_limit = 10;
		rc.aflags = 0;
		ret = wl1271_acx_ap_rate_policy(wl, &rc,
						wlvif->ap.ucast_rate_idx[i]);
		if (ret < 0)
			return ret;
	}

	return 0;
}