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
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271_acx_rssi_snr_avg_weights {int /*<<< orphan*/  snr_data; int /*<<< orphan*/  snr_beacon; int /*<<< orphan*/  rssi_data; int /*<<< orphan*/  rssi_beacon; int /*<<< orphan*/  role_id; } ;
struct conf_roam_trigger_settings {int /*<<< orphan*/  avg_weight_snr_data; int /*<<< orphan*/  avg_weight_snr_beacon; int /*<<< orphan*/  avg_weight_rssi_data; int /*<<< orphan*/  avg_weight_rssi_beacon; } ;
struct TYPE_2__ {struct conf_roam_trigger_settings roam_trigger; } ;
struct wl1271 {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_RSSI_SNR_WEIGHTS ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_rssi_snr_avg_weights*) ; 
 struct wl1271_acx_rssi_snr_avg_weights* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_rssi_snr_avg_weights*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_rssi_snr_avg_weights(struct wl1271 *wl,
				    struct wl12xx_vif *wlvif)
{
	struct wl1271_acx_rssi_snr_avg_weights *acx = NULL;
	struct conf_roam_trigger_settings *c = &wl->conf.roam_trigger;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx rssi snr avg weights");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->role_id = wlvif->role_id;
	acx->rssi_beacon = c->avg_weight_rssi_beacon;
	acx->rssi_data = c->avg_weight_rssi_data;
	acx->snr_beacon = c->avg_weight_snr_beacon;
	acx->snr_data = c->avg_weight_snr_data;

	ret = wl1271_cmd_configure(wl, ACX_RSSI_SNR_WEIGHTS, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx rssi snr trigger weights failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}