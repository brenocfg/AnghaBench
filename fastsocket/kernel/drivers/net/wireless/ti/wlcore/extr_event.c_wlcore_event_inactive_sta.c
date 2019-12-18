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
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wlcore_disconnect_sta (struct wl1271*,unsigned long) ; 

void wlcore_event_inactive_sta(struct wl1271 *wl, unsigned long sta_bitmap)
{
	wl1271_debug(DEBUG_EVENT, "INACTIVE_STA_EVENT_ID");
	wlcore_disconnect_sta(wl, sta_bitmap);
}