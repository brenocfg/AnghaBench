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
struct intel_lvds_encoder {int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int LVDS_PORT_EN ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  PCH_PP_STATUS ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int POWER_TARGET_ON ; 
 int /*<<< orphan*/  PP_CONTROL ; 
 int PP_ON ; 
 int /*<<< orphan*/  PP_STATUS ; 
 int /*<<< orphan*/  intel_panel_enable_backlight (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_lvds_encoder* to_lvds_encoder (TYPE_1__*) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void intel_enable_lvds(struct intel_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct intel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->base.crtc);
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 ctl_reg, stat_reg;

	if (HAS_PCH_SPLIT(dev)) {
		ctl_reg = PCH_PP_CONTROL;
		stat_reg = PCH_PP_STATUS;
	} else {
		ctl_reg = PP_CONTROL;
		stat_reg = PP_STATUS;
	}

	I915_WRITE(lvds_encoder->reg, I915_READ(lvds_encoder->reg) | LVDS_PORT_EN);

	I915_WRITE(ctl_reg, I915_READ(ctl_reg) | POWER_TARGET_ON);
	POSTING_READ(lvds_encoder->reg);
	if (wait_for((I915_READ(stat_reg) & PP_ON) != 0, 1000))
		DRM_ERROR("timed out waiting for panel to power on\n");

	intel_panel_enable_backlight(dev, intel_crtc->pipe);
}