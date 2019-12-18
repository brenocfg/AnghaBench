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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl1251 {int dummy; } ;
struct cmd_enabledisable_path {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DISABLE_RX ; 
 int /*<<< orphan*/  CMD_DISABLE_TX ; 
 int /*<<< orphan*/  CMD_ENABLE_RX ; 
 int /*<<< orphan*/  CMD_ENABLE_TX ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct cmd_enabledisable_path*) ; 
 struct cmd_enabledisable_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_send (struct wl1251*,int /*<<< orphan*/ ,struct cmd_enabledisable_path*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wl1251_error (char*,char*,int /*<<< orphan*/ ) ; 

int wl1251_cmd_data_path(struct wl1251 *wl, u8 channel, bool enable)
{
	struct cmd_enabledisable_path *cmd;
	int ret;
	u16 cmd_rx, cmd_tx;

	wl1251_debug(DEBUG_CMD, "cmd data path");

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->channel = channel;

	if (enable) {
		cmd_rx = CMD_ENABLE_RX;
		cmd_tx = CMD_ENABLE_TX;
	} else {
		cmd_rx = CMD_DISABLE_RX;
		cmd_tx = CMD_DISABLE_TX;
	}

	ret = wl1251_cmd_send(wl, cmd_rx, cmd, sizeof(*cmd));
	if (ret < 0) {
		wl1251_error("rx %s cmd for channel %d failed",
			     enable ? "start" : "stop", channel);
		goto out;
	}

	wl1251_debug(DEBUG_BOOT, "rx %s cmd channel %d",
		     enable ? "start" : "stop", channel);

	ret = wl1251_cmd_send(wl, cmd_tx, cmd, sizeof(*cmd));
	if (ret < 0) {
		wl1251_error("tx %s cmd for channel %d failed",
			     enable ? "start" : "stop", channel);
		goto out;
	}

	wl1251_debug(DEBUG_BOOT, "tx %s cmd channel %d",
		     enable ? "start" : "stop", channel);

out:
	kfree(cmd);
	return ret;
}