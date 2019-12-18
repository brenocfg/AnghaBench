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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int /*<<< orphan*/  panel_power_down_delay; int /*<<< orphan*/  want_panel_vdd; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_1__ mode_config; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDP_FORCE_VDD ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  PCH_PP_STATUS ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 scalar_t__ ironlake_edp_have_panel_vdd (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_get_pp_control (struct drm_i915_private*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ironlake_panel_vdd_off_sync(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 pp;

	WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));

	if (!intel_dp->want_panel_vdd && ironlake_edp_have_panel_vdd(intel_dp)) {
		pp = ironlake_get_pp_control(dev_priv);
		pp &= ~EDP_FORCE_VDD;
		I915_WRITE(PCH_PP_CONTROL, pp);
		POSTING_READ(PCH_PP_CONTROL);

		/* Make sure sequencer is idle before allowing subsequent activity */
		DRM_DEBUG_KMS("PCH_PP_STATUS: 0x%08x PCH_PP_CONTROL: 0x%08x\n",
			      I915_READ(PCH_PP_STATUS), I915_READ(PCH_PP_CONTROL));

		msleep(intel_dp->panel_power_down_delay);
	}
}