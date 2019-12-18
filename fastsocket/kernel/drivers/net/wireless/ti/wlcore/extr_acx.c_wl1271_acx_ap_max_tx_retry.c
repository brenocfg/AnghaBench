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
struct wl1271_acx_ap_max_tx_retry {int /*<<< orphan*/  max_tx_retry; int /*<<< orphan*/  role_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_tx_retries; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct wl1271 {TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_MAX_TX_FAILURE ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_ap_max_tx_retry*) ; 
 struct wl1271_acx_ap_max_tx_retry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_ap_max_tx_retry*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_ap_max_tx_retry(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct wl1271_acx_ap_max_tx_retry *acx = NULL;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx ap max tx retry");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	acx->role_id = wlvif->role_id;
	acx->max_tx_retry = cpu_to_le16(wl->conf.tx.max_tx_retries);

	ret = wl1271_cmd_configure(wl, ACX_MAX_TX_FAILURE, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx ap max tx retry failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}