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
struct wl1271 {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SCAN ; 
 int /*<<< orphan*/  ieee80211_sched_scan_results (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 

void wlcore_scan_sched_scan_results(struct wl1271 *wl)
{
	wl1271_debug(DEBUG_SCAN, "got periodic scan results");

	ieee80211_sched_scan_results(wl->hw);
}