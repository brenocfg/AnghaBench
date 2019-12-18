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
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
struct acx_roaming_stats {int /*<<< orphan*/  rssi_beacon; int /*<<< orphan*/  role_id; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_ROAMING_STATISTICS_TBL ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_roaming_stats*) ; 
 struct acx_roaming_stats* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_interrogate (struct wl1271*,int /*<<< orphan*/ ,struct acx_roaming_stats*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wlcore_acx_average_rssi(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			    s8 *avg_rssi)
{
	struct acx_roaming_stats *acx;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx roaming statistics");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->role_id = wlvif->role_id;
	ret = wl1271_cmd_interrogate(wl, ACX_ROAMING_STATISTICS_TBL,
				     acx, sizeof(*acx));
	if (ret	< 0) {
		wl1271_warning("acx roaming statistics failed: %d", ret);
		ret = -ENOMEM;
		goto out;
	}

	*avg_rssi = acx->rssi_beacon;
out:
	kfree(acx);
	return ret;
}