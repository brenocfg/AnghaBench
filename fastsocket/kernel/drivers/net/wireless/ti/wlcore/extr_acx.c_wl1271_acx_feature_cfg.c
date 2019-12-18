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
struct acx_feature_config {scalar_t__ options; scalar_t__ data_flow_options; int /*<<< orphan*/  role_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_FEATURE_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_feature_config*) ; 
 struct acx_feature_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_feature_config*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl1271_acx_feature_cfg(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	struct acx_feature_config *feature;
	int ret;

	wl1271_debug(DEBUG_ACX, "acx feature cfg");

	feature = kzalloc(sizeof(*feature), GFP_KERNEL);
	if (!feature) {
		ret = -ENOMEM;
		goto out;
	}

	/* DF_ENCRYPTION_DISABLE and DF_SNIFF_MODE_ENABLE are disabled */
	feature->role_id = wlvif->role_id;
	feature->data_flow_options = 0;
	feature->options = 0;

	ret = wl1271_cmd_configure(wl, ACX_FEATURE_CFG,
				   feature, sizeof(*feature));
	if (ret < 0) {
		wl1271_error("Couldnt set HW encryption");
		goto out;
	}

out:
	kfree(feature);
	return ret;
}