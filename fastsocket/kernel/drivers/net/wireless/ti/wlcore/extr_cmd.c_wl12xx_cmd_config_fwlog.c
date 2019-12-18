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
struct wl12xx_cmd_config_fwlog {int /*<<< orphan*/  threshold; int /*<<< orphan*/  output; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  log_severity; int /*<<< orphan*/  logger_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  threshold; int /*<<< orphan*/  output; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  severity; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {TYPE_1__ fwlog; } ;
struct wl1271 {TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CONFIG_FWLOGGER ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_config_fwlog*) ; 
 struct wl12xx_cmd_config_fwlog* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_config_fwlog*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl12xx_cmd_config_fwlog(struct wl1271 *wl)
{
	struct wl12xx_cmd_config_fwlog *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd config firmware logger");

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->logger_mode = wl->conf.fwlog.mode;
	cmd->log_severity = wl->conf.fwlog.severity;
	cmd->timestamp = wl->conf.fwlog.timestamp;
	cmd->output = wl->conf.fwlog.output;
	cmd->threshold = wl->conf.fwlog.threshold;

	ret = wl1271_cmd_send(wl, CMD_CONFIG_FWLOGGER, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send config firmware logger command");
		goto out_free;
	}

out_free:
	kfree(cmd);

out:
	return ret;
}