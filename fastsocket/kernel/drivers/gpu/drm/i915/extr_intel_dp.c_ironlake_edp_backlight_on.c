#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int /*<<< orphan*/  backlight_on_delay; } ;
struct TYPE_5__ {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_2__ base; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_6__ {int pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  EDP_BLC_ENABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_panel_enable_backlight (struct drm_device*,int) ; 
 int /*<<< orphan*/  ironlake_get_pp_control (struct drm_i915_private*) ; 
 int /*<<< orphan*/  is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_intel_crtc (int /*<<< orphan*/ ) ; 

void ironlake_edp_backlight_on(struct intel_dp *intel_dp)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	int pipe = to_intel_crtc(intel_dig_port->base.base.crtc)->pipe;
	u32 pp;

	if (!is_edp(intel_dp))
		return;

	DRM_DEBUG_KMS("\n");
	/*
	 * If we enable the backlight right away following a panel power
	 * on, we may see slight flicker as the panel syncs with the eDP
	 * link.  So delay a bit to make sure the image is solid before
	 * allowing it to appear.
	 */
	msleep(intel_dp->backlight_on_delay);
	pp = ironlake_get_pp_control(dev_priv);
	pp |= EDP_BLC_ENABLE;
	I915_WRITE(PCH_PP_CONTROL, pp);
	POSTING_READ(PCH_PP_CONTROL);

	intel_panel_enable_backlight(dev, pipe);
}