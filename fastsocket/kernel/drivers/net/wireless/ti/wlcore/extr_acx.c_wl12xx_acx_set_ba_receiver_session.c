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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl1271_acx_ba_receiver_setup {int hlid; int tid; int enable; int /*<<< orphan*/  ssn; int /*<<< orphan*/  win_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_ba_win_size; } ;
struct TYPE_4__ {TYPE_1__ ht; } ;
struct wl1271 {TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_BA_SESSION_RX_SETUP ; 
 int /*<<< orphan*/  BIT (int) ; 
 int CMD_STATUS_NO_RX_BA_SESSION ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_ba_receiver_setup*) ; 
 struct wl1271_acx_ba_receiver_setup* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 
 int wlcore_cmd_configure_failsafe (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_ba_receiver_setup*,int,int /*<<< orphan*/ ) ; 

int wl12xx_acx_set_ba_receiver_session(struct wl1271 *wl, u8 tid_index,
				       u16 ssn, bool enable, u8 peer_hlid)
{
	struct wl1271_acx_ba_receiver_setup *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx ba receiver session setting");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->hlid = peer_hlid;
	acx->tid = tid_index;
	acx->enable = enable;
	acx->win_size = wl->conf.ht.rx_ba_win_size;
	acx->ssn = ssn;

	ret = wlcore_cmd_configure_failsafe(wl, ACX_BA_SESSION_RX_SETUP, acx,
					    sizeof(*acx),
					    BIT(CMD_STATUS_NO_RX_BA_SESSION));
	if (ret < 0) {
		wl1271_warning("acx ba receiver session failed: %d", ret);
		goto out;
	}

	/* sometimes we can't start the session */
	if (ret == CMD_STATUS_NO_RX_BA_SESSION) {
		wl1271_warning("no fw rx ba on tid %d", tid_index);
		ret = -EBUSY;
		goto out;
	}

	ret = 0;
out:
	kfree(acx);
	return ret;
}