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
struct intel_dp {int* dpcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_BRANCH_OUI ; 
 size_t DP_DOWN_STREAM_PORT_COUNT ; 
 int DP_OUI_SUPPORT ; 
 int /*<<< orphan*/  DP_SINK_OUI ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_dp_aux_native_read_retry (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ironlake_edp_panel_vdd_off (struct intel_dp*,int) ; 
 int /*<<< orphan*/  ironlake_edp_panel_vdd_on (struct intel_dp*) ; 

__attribute__((used)) static void
intel_dp_probe_oui(struct intel_dp *intel_dp)
{
	u8 buf[3];

	if (!(intel_dp->dpcd[DP_DOWN_STREAM_PORT_COUNT] & DP_OUI_SUPPORT))
		return;

	ironlake_edp_panel_vdd_on(intel_dp);

	if (intel_dp_aux_native_read_retry(intel_dp, DP_SINK_OUI, buf, 3))
		DRM_DEBUG_KMS("Sink OUI: %02hx%02hx%02hx\n",
			      buf[0], buf[1], buf[2]);

	if (intel_dp_aux_native_read_retry(intel_dp, DP_BRANCH_OUI, buf, 3))
		DRM_DEBUG_KMS("Branch OUI: %02hx%02hx%02hx\n",
			      buf[0], buf[1], buf[2]);

	ironlake_edp_panel_vdd_off(intel_dp, false);
}