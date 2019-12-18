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
typedef  scalar_t__ u8 ;
struct wl12xx_cmd_remove_peer {scalar_t__ send_deauth_flag; scalar_t__ reason_opcode; scalar_t__ hlid; } ;
struct wl1271 {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* wait_for_event ) (struct wl1271*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_REMOVE_PEER ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WLCORE_EVENT_PEER_REMOVE_COMPLETE ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_remove_peer*) ; 
 struct wl12xx_cmd_remove_peer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct wl1271*,int /*<<< orphan*/ ,int*) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_remove_peer*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int /*<<< orphan*/  wl12xx_queue_recovery_work (struct wl1271*) ; 

int wl12xx_cmd_remove_peer(struct wl1271 *wl, u8 hlid)
{
	struct wl12xx_cmd_remove_peer *cmd;
	int ret;
	bool timeout = false;

	wl1271_debug(DEBUG_CMD, "cmd remove peer %d", (int)hlid);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->hlid = hlid;
	/* We never send a deauth, mac80211 is in charge of this */
	cmd->reason_opcode = 0;
	cmd->send_deauth_flag = 0;

	ret = wl1271_cmd_send(wl, CMD_REMOVE_PEER, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to initiate cmd remove peer");
		goto out_free;
	}

	ret = wl->ops->wait_for_event(wl,
				      WLCORE_EVENT_PEER_REMOVE_COMPLETE,
				      &timeout);

	/*
	 * We are ok with a timeout here. The event is sometimes not sent
	 * due to a firmware bug. In case of another error (like SDIO timeout)
	 * queue a recovery.
	 */
	if (ret)
		wl12xx_queue_recovery_work(wl);

out_free:
	kfree(cmd);

out:
	return ret;
}