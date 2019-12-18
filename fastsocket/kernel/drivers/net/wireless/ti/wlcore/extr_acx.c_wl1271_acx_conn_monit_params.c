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
typedef  int /*<<< orphan*/  u32 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  bss_lose_timeout; int /*<<< orphan*/  synch_fail_thold; } ;
struct TYPE_4__ {TYPE_1__ conn; } ;
struct wl1271 {TYPE_2__ conf; } ;
struct acx_conn_monit_params {void* bss_lose_timeout; void* synch_fail_thold; int /*<<< orphan*/  role_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_CONN_MONIT_DISABLE_VALUE ; 
 int /*<<< orphan*/  ACX_CONN_MONIT_PARAMS ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acx_conn_monit_params*) ; 
 struct acx_conn_monit_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_conn_monit_params*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_conn_monit_params(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				 bool enable)
{
	struct acx_conn_monit_params *acx;
	u32 threshold = ACX_CONN_MONIT_DISABLE_VALUE;
	u32 timeout = ACX_CONN_MONIT_DISABLE_VALUE;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx connection monitor parameters: %s",
		     enable ? "enabled" : "disabled");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	if (enable) {
		threshold = wl->conf.conn.synch_fail_thold;
		timeout = wl->conf.conn.bss_lose_timeout;
	}

	acx->role_id = wlvif->role_id;
	acx->synch_fail_thold = cpu_to_le32(threshold);
	acx->bss_lose_timeout = cpu_to_le32(timeout);

	ret = wl1271_cmd_configure(wl, ACX_CONN_MONIT_PARAMS,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("failed to set connection monitor "
			       "parameters: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}