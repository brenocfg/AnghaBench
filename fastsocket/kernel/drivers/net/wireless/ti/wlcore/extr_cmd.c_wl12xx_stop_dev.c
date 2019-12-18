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
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  dev_role_id; } ;
struct wl1271 {int /*<<< orphan*/  roc_map; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_IBSS ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl12xx_cmd_role_disable (struct wl1271*,int /*<<< orphan*/ *) ; 
 int wl12xx_cmd_role_stop_dev (struct wl1271*,struct wl12xx_vif*) ; 
 int wl12xx_croc (struct wl1271*,int /*<<< orphan*/ ) ; 
 int wlcore_tx_work_locked (struct wl1271*) ; 

int wl12xx_stop_dev(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;

	if (WARN_ON(!(wlvif->bss_type == BSS_TYPE_STA_BSS ||
		      wlvif->bss_type == BSS_TYPE_IBSS)))
		return -EINVAL;

	/* flush all pending packets */
	ret = wlcore_tx_work_locked(wl);
	if (ret < 0)
		goto out;

	if (test_bit(wlvif->dev_role_id, wl->roc_map)) {
		ret = wl12xx_croc(wl, wlvif->dev_role_id);
		if (ret < 0)
			goto out;
	}

	ret = wl12xx_cmd_role_stop_dev(wl, wlvif);
	if (ret < 0)
		goto out;

	ret = wl12xx_cmd_role_disable(wl, &wlvif->dev_role_id);
	if (ret < 0)
		goto out;

out:
	return ret;
}