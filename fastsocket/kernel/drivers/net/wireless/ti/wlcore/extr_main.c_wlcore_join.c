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
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  encryption_type; int /*<<< orphan*/  flags; } ;
struct wl1271 {int quirks; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_IBSS ; 
 int /*<<< orphan*/  KEY_NONE ; 
 int WLCORE_QUIRK_START_STA_FAILS ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_ASSOCIATED ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_info (char*) ; 
 int wl12xx_cmd_role_start_ibss (struct wl1271*,struct wl12xx_vif*) ; 
 int wl12xx_cmd_role_start_sta (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl12xx_cmd_role_stop_sta (struct wl1271*,struct wl12xx_vif*) ; 

__attribute__((used)) static int wlcore_join(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret;
	bool is_ibss = (wlvif->bss_type == BSS_TYPE_IBSS);

	/*
	 * One of the side effects of the JOIN command is that is clears
	 * WPA/WPA2 keys from the chipset. Performing a JOIN while associated
	 * to a WPA/WPA2 access point will therefore kill the data-path.
	 * Currently the only valid scenario for JOIN during association
	 * is on roaming, in which case we will also be given new keys.
	 * Keep the below message for now, unless it starts bothering
	 * users who really like to roam a lot :)
	 */
	if (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags))
		wl1271_info("JOIN while associated.");

	/* clear encryption type */
	wlvif->encryption_type = KEY_NONE;

	if (is_ibss)
		ret = wl12xx_cmd_role_start_ibss(wl, wlvif);
	else {
		if (wl->quirks & WLCORE_QUIRK_START_STA_FAILS) {
			/*
			 * TODO: this is an ugly workaround for wl12xx fw
			 * bug - we are not able to tx/rx after the first
			 * start_sta, so make dummy start+stop calls,
			 * and then call start_sta again.
			 * this should be fixed in the fw.
			 */
			wl12xx_cmd_role_start_sta(wl, wlvif);
			wl12xx_cmd_role_stop_sta(wl, wlvif);
		}

		ret = wl12xx_cmd_role_start_sta(wl, wlvif);
	}

	return ret;
}