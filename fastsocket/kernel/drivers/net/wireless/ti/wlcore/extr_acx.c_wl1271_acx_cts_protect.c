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
struct wl1271 {int dummy; } ;
struct acx_ctsprotect {int ctsprotect; int /*<<< orphan*/  role_id; } ;
typedef  enum acx_ctsprotect_type { ____Placeholder_acx_ctsprotect_type } acx_ctsprotect_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_CTS_PROTECTION ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_ctsprotect*) ; 
 struct acx_ctsprotect* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_ctsprotect*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_cts_protect(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			   enum acx_ctsprotect_type ctsprotect)
{
	struct acx_ctsprotect *acx;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx_set_ctsprotect");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->role_id = wlvif->role_id;
	acx->ctsprotect = ctsprotect;

	ret = wl1271_cmd_configure(wl, ACX_CTS_PROTECTION, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("Setting of ctsprotect failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}