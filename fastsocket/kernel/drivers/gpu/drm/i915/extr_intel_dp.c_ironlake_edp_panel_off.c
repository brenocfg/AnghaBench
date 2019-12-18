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
typedef  int u32 ;
struct intel_dp {int want_panel_vdd; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EDP_BLC_ENABLE ; 
 int EDP_FORCE_VDD ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PANEL_POWER_RESET ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int POWER_TARGET_ON ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 int ironlake_get_pp_control (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ironlake_wait_panel_off (struct intel_dp*) ; 
 int /*<<< orphan*/  is_edp (struct intel_dp*) ; 

void ironlake_edp_panel_off(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 pp;

	if (!is_edp(intel_dp))
		return;

	DRM_DEBUG_KMS("Turn eDP power off\n");

	WARN(!intel_dp->want_panel_vdd, "Need VDD to turn off panel\n");

	pp = ironlake_get_pp_control(dev_priv);
	/* We need to switch off panel power _and_ force vdd, for otherwise some
	 * panels get very unhappy and cease to work. */
	pp &= ~(POWER_TARGET_ON | EDP_FORCE_VDD | PANEL_POWER_RESET | EDP_BLC_ENABLE);
	I915_WRITE(PCH_PP_CONTROL, pp);
	POSTING_READ(PCH_PP_CONTROL);

	intel_dp->want_panel_vdd = false;

	ironlake_wait_panel_off(intel_dp);
}