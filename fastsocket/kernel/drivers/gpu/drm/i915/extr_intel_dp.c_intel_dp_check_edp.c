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
struct intel_dp {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  PCH_PP_STATUS ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_have_panel_power (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_edp_have_panel_vdd (struct intel_dp*) ; 
 int /*<<< orphan*/  is_edp (struct intel_dp*) ; 

__attribute__((used)) static void
intel_dp_check_edp(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!is_edp(intel_dp))
		return;
	if (!ironlake_edp_have_panel_power(intel_dp) && !ironlake_edp_have_panel_vdd(intel_dp)) {
		WARN(1, "eDP powered off while attempting aux channel communication.\n");
		DRM_DEBUG_KMS("Status 0x%08x Control 0x%08x\n",
			      I915_READ(PCH_PP_STATUS),
			      I915_READ(PCH_PP_CONTROL));
	}
}