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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_link_down (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ironlake_edp_backlight_off (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_panel_off (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_panel_vdd_on (struct intel_dp*) ; 
 int /*<<< orphan*/  is_cpu_edp (struct intel_dp*) ; 

__attribute__((used)) static void intel_disable_dp(struct intel_encoder *encoder)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);

	/* Make sure the panel is off before trying to change the mode. But also
	 * ensure that we have vdd while we switch off the panel. */
	ironlake_edp_panel_vdd_on(intel_dp);
	ironlake_edp_backlight_off(intel_dp);
	intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);
	ironlake_edp_panel_off(intel_dp);

	/* cpu edp my only be disable _after_ the cpu pipe/plane is disabled. */
	if (!is_cpu_edp(intel_dp))
		intel_dp_link_down(intel_dp);
}