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
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  dev_role_id; } ;
struct wl1271 {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_IBSS ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WL1271_ROLE_DEVICE ; 
 int /*<<< orphan*/  wl12xx_cmd_role_disable (struct wl1271*,int /*<<< orphan*/ *) ; 
 int wl12xx_cmd_role_enable (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl12xx_cmd_role_start_dev (struct wl1271*,struct wl12xx_vif*,int,int) ; 
 int /*<<< orphan*/  wl12xx_cmd_role_stop_dev (struct wl1271*,struct wl12xx_vif*) ; 
 int wl12xx_roc (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 

int wl12xx_start_dev(struct wl1271 *wl, struct wl12xx_vif *wlvif,
		     enum ieee80211_band band, int channel)
{
	int ret;

	if (WARN_ON(!(wlvif->bss_type == BSS_TYPE_STA_BSS ||
		      wlvif->bss_type == BSS_TYPE_IBSS)))
		return -EINVAL;

	ret = wl12xx_cmd_role_enable(wl,
				     wl12xx_wlvif_to_vif(wlvif)->addr,
				     WL1271_ROLE_DEVICE,
				     &wlvif->dev_role_id);
	if (ret < 0)
		goto out;

	ret = wl12xx_cmd_role_start_dev(wl, wlvif, band, channel);
	if (ret < 0)
		goto out_disable;

	ret = wl12xx_roc(wl, wlvif, wlvif->dev_role_id, band, channel);
	if (ret < 0)
		goto out_stop;

	return 0;

out_stop:
	wl12xx_cmd_role_stop_dev(wl, wlvif);
out_disable:
	wl12xx_cmd_role_disable(wl, &wlvif->dev_role_id);
out:
	return ret;
}