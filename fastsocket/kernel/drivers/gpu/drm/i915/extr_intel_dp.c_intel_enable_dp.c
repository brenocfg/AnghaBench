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
typedef  int uint32_t ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_dp {int /*<<< orphan*/  output_reg; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int DP_PORT_EN ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_dp_complete_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_sink_dpms (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_start_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_backlight_on (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_panel_on (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_panel_vdd_off (struct intel_dp*,int) ; 
 int /*<<< orphan*/  ironlake_edp_panel_vdd_on (struct intel_dp*) ; 

__attribute__((used)) static void intel_enable_dp(struct intel_encoder *encoder)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t dp_reg = I915_READ(intel_dp->output_reg);

	if (WARN_ON(dp_reg & DP_PORT_EN))
		return;

	ironlake_edp_panel_vdd_on(intel_dp);
	intel_dp_sink_dpms(intel_dp, DRM_MODE_DPMS_ON);
	intel_dp_start_link_train(intel_dp);
	ironlake_edp_panel_on(intel_dp);
	ironlake_edp_panel_vdd_off(intel_dp, true);
	intel_dp_complete_link_train(intel_dp);
	ironlake_edp_backlight_on(intel_dp);
}