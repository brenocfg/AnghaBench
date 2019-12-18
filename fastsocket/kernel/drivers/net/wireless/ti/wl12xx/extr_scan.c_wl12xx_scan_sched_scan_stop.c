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
struct wl1271_cmd_sched_scan_stop {int /*<<< orphan*/  tag; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STOP_PERIODIC_SCAN ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WL1271_SCAN_DEFAULT_TAG ; 
 int /*<<< orphan*/  kfree (struct wl1271_cmd_sched_scan_stop*) ; 
 struct wl1271_cmd_sched_scan_stop* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_cmd_sched_scan_stop*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

void wl12xx_scan_sched_scan_stop(struct wl1271 *wl,  struct wl12xx_vif *wlvif)
{
	struct wl1271_cmd_sched_scan_stop *stop;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd periodic scan stop");

	/* FIXME: what to do if alloc'ing to stop fails? */
	stop = kzalloc(sizeof(*stop), GFP_KERNEL);
	if (!stop) {
		wl1271_error("failed to alloc memory to send sched scan stop");
		return;
	}

	stop->role_id = wlvif->role_id;
	stop->tag = WL1271_SCAN_DEFAULT_TAG;

	ret = wl1271_cmd_send(wl, CMD_STOP_PERIODIC_SCAN, stop,
			      sizeof(*stop), 0);
	if (ret < 0) {
		wl1271_error("failed to send sched scan stop command");
		goto out_free;
	}

out_free:
	kfree(stop);
}