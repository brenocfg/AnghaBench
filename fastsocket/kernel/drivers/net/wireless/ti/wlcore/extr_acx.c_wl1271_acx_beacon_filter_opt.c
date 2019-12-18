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
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct TYPE_4__ {scalar_t__ bcn_filt_mode; } ;
struct TYPE_3__ {TYPE_2__ conn; } ;
struct wl1271 {TYPE_1__ conf; } ;
struct acx_beacon_filter_option {int enable; scalar_t__ max_num_beacons; int /*<<< orphan*/  role_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_BEACON_FILTER_OPT ; 
 scalar_t__ CONF_BCN_FILT_MODE_DISABLED ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_beacon_filter_option*) ; 
 struct acx_beacon_filter_option* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_beacon_filter_option*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_beacon_filter_opt(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				 bool enable_filter)
{
	struct acx_beacon_filter_option *beacon_filter = NULL;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx beacon filter opt");

	if (enable_filter &&
	    wl->conf.conn.bcn_filt_mode == CONF_BCN_FILT_MODE_DISABLED)
		goto out;

	beacon_filter = kzalloc(sizeof(*beacon_filter), GFP_KERNEL);
	if (!beacon_filter) {
		ret = -ENOMEM;
		goto out;
	}

	beacon_filter->role_id = wlvif->role_id;
	beacon_filter->enable = enable_filter;

	/*
	 * When set to zero, and the filter is enabled, beacons
	 * without the unicast TIM bit set are dropped.
	 */
	beacon_filter->max_num_beacons = 0;

	ret = wl1271_cmd_configure(wl, ACX_BEACON_FILTER_OPT,
				   beacon_filter, sizeof(*beacon_filter));
	if (ret < 0) {
		wl1271_warning("failed to set beacon filter opt: %d", ret);
		goto out;
	}

out:
	kfree(beacon_filter);
	return ret;
}