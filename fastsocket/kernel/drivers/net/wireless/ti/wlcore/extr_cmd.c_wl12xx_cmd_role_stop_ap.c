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
struct TYPE_2__ {int /*<<< orphan*/  global_hlid; int /*<<< orphan*/  bcast_hlid; } ;
struct wl12xx_vif {TYPE_1__ ap; int /*<<< orphan*/  role_id; } ;
struct wl12xx_cmd_role_stop {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ROLE_STOP ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_role_stop*) ; 
 struct wl12xx_cmd_role_stop* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_role_stop*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int /*<<< orphan*/  wl12xx_free_link (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ *) ; 

int wl12xx_cmd_role_stop_ap(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct wl12xx_cmd_role_stop *cmd;
	int ret;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	wl1271_debug(DEBUG_CMD, "cmd role stop ap %d", wlvif->role_id);

	cmd->role_id = wlvif->role_id;

	ret = wl1271_cmd_send(wl, CMD_ROLE_STOP, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to initiate cmd role stop ap");
		goto out_free;
	}

	wl12xx_free_link(wl, wlvif, &wlvif->ap.bcast_hlid);
	wl12xx_free_link(wl, wlvif, &wlvif->ap.global_hlid);

out_free:
	kfree(cmd);

out:
	return ret;
}