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
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271_acx_bet_enable {int /*<<< orphan*/  max_consecutive; scalar_t__ enable; int /*<<< orphan*/  role_id; } ;
struct TYPE_3__ {scalar_t__ bet_enable; int /*<<< orphan*/  bet_max_consecutive; } ;
struct TYPE_4__ {TYPE_1__ conn; } ;
struct wl1271 {TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_BET_ENABLE ; 
 scalar_t__ CONF_BET_MODE_DISABLE ; 
 scalar_t__ CONF_BET_MODE_ENABLE ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_bet_enable*) ; 
 struct wl1271_acx_bet_enable* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_bet_enable*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_bet_enable(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			  bool enable)
{
	struct wl1271_acx_bet_enable *acx = NULL;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx bet enable");

	if (enable && wl->conf.conn.bet_enable == CONF_BET_MODE_DISABLE)
		goto out;

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->role_id = wlvif->role_id;
	acx->enable = enable ? CONF_BET_MODE_ENABLE : CONF_BET_MODE_DISABLE;
	acx->max_consecutive = wl->conf.conn.bet_max_consecutive;

	ret = wl1271_cmd_configure(wl, ACX_BET_ENABLE, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx bet enable failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}