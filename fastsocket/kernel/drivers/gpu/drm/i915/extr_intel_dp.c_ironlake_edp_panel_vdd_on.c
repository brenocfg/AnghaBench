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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int want_panel_vdd; int /*<<< orphan*/  panel_power_up_delay; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  EDP_FORCE_VDD ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  PCH_PP_STATUS ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_have_panel_power (struct intel_dp*) ; 
 scalar_t__ ironlake_edp_have_panel_vdd (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_get_pp_control (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ironlake_wait_panel_power_cycle (struct intel_dp*) ; 
 int /*<<< orphan*/  is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

void ironlake_edp_panel_vdd_on(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 pp;

	if (!is_edp(intel_dp))
		return;
	DRM_DEBUG_KMS("Turn eDP VDD on\n");

	WARN(intel_dp->want_panel_vdd,
	     "eDP VDD already requested on\n");

	intel_dp->want_panel_vdd = true;

	if (ironlake_edp_have_panel_vdd(intel_dp)) {
		DRM_DEBUG_KMS("eDP VDD already on\n");
		return;
	}

	if (!ironlake_edp_have_panel_power(intel_dp))
		ironlake_wait_panel_power_cycle(intel_dp);

	pp = ironlake_get_pp_control(dev_priv);
	pp |= EDP_FORCE_VDD;
	I915_WRITE(PCH_PP_CONTROL, pp);
	POSTING_READ(PCH_PP_CONTROL);
	DRM_DEBUG_KMS("PCH_PP_STATUS: 0x%08x PCH_PP_CONTROL: 0x%08x\n",
		      I915_READ(PCH_PP_STATUS), I915_READ(PCH_PP_CONTROL));

	/*
	 * If the panel wasn't on, delay before accessing aux channel
	 */
	if (!ironlake_edp_have_panel_power(intel_dp)) {
		DRM_DEBUG_KMS("eDP was not running\n");
		msleep(intel_dp->panel_power_up_delay);
	}
}