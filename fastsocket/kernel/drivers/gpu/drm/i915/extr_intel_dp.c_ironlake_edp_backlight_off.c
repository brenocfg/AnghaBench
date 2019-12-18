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
struct intel_dp {int /*<<< orphan*/  backlight_off_delay; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  EDP_BLC_ENABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_panel_disable_backlight (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_get_pp_control (struct drm_i915_private*) ; 
 int /*<<< orphan*/  is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

void ironlake_edp_backlight_off(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 pp;

	if (!is_edp(intel_dp))
		return;

	intel_panel_disable_backlight(dev);

	DRM_DEBUG_KMS("\n");
	pp = ironlake_get_pp_control(dev_priv);
	pp &= ~EDP_BLC_ENABLE;
	I915_WRITE(PCH_PP_CONTROL, pp);
	POSTING_READ(PCH_PP_CONTROL);
	msleep(intel_dp->backlight_off_delay);
}