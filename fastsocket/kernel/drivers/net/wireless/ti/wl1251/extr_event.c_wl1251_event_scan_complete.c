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
struct wl1251 {int scanning; TYPE_2__* hw; } ;
struct event_mailbox {int /*<<< orphan*/  scheduled_scan_channels; int /*<<< orphan*/  scheduled_scan_status; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int IEEE80211_CONF_IDLE ; 
 int /*<<< orphan*/  STATION_IDLE ; 
 int /*<<< orphan*/  ieee80211_scan_completed (TYPE_2__*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,...) ; 
 int wl1251_ps_set_mode (struct wl1251*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1251_event_scan_complete(struct wl1251 *wl,
				      struct event_mailbox *mbox)
{
	int ret = 0;

	wl1251_debug(DEBUG_EVENT, "status: 0x%x, channels: %d",
		     mbox->scheduled_scan_status,
		     mbox->scheduled_scan_channels);

	if (wl->scanning) {
		ieee80211_scan_completed(wl->hw, false);
		wl1251_debug(DEBUG_MAC80211, "mac80211 hw scan completed");
		wl->scanning = false;
		if (wl->hw->conf.flags & IEEE80211_CONF_IDLE)
			ret = wl1251_ps_set_mode(wl, STATION_IDLE);
	}

	return ret;
}