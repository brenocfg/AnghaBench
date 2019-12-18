#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_lvds_encoder {int /*<<< orphan*/  reg; scalar_t__ is_dual_link; TYPE_3__* attached_connector; } ;
struct TYPE_9__ {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct intel_encoder {TYPE_4__ base; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int lvds_border_bits; scalar_t__ lvds_dither; } ;
struct drm_display_mode {int flags; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_10__ {int gen; } ;
struct TYPE_6__ {struct drm_display_mode* fixed_mode; } ;
struct TYPE_7__ {TYPE_1__ panel; } ;
struct TYPE_8__ {TYPE_2__ base; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 scalar_t__ HAS_PCH_CPT (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* INTEL_INFO (struct drm_device*) ; 
 int LVDS_A0A2_CLKA_POWER_UP ; 
 int LVDS_B0B3_POWER_UP ; 
 int LVDS_CLKB_POWER_UP ; 
 int LVDS_ENABLE_DITHER ; 
 int LVDS_HSYNC_POLARITY ; 
 int LVDS_PIPEB_SELECT ; 
 int LVDS_PORT_EN ; 
 int LVDS_VSYNC_POLARITY ; 
 int PORT_TRANS_SEL_CPT (int) ; 
 int PORT_TRANS_SEL_MASK ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_lvds_encoder* to_lvds_encoder (TYPE_4__*) ; 

__attribute__((used)) static void intel_pre_pll_enable_lvds(struct intel_encoder *encoder)
{
	struct intel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->base.crtc);
	struct drm_display_mode *fixed_mode =
		lvds_encoder->attached_connector->base.panel.fixed_mode;
	int pipe = intel_crtc->pipe;
	u32 temp;

	temp = I915_READ(lvds_encoder->reg);
	temp |= LVDS_PORT_EN | LVDS_A0A2_CLKA_POWER_UP;

	if (HAS_PCH_CPT(dev)) {
		temp &= ~PORT_TRANS_SEL_MASK;
		temp |= PORT_TRANS_SEL_CPT(pipe);
	} else {
		if (pipe == 1) {
			temp |= LVDS_PIPEB_SELECT;
		} else {
			temp &= ~LVDS_PIPEB_SELECT;
		}
	}

	/* set the corresponsding LVDS_BORDER bit */
	temp |= dev_priv->lvds_border_bits;
	/* Set the B0-B3 data pairs corresponding to whether we're going to
	 * set the DPLLs for dual-channel mode or not.
	 */
	if (lvds_encoder->is_dual_link)
		temp |= LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP;
	else
		temp &= ~(LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP);

	/* It would be nice to set 24 vs 18-bit mode (LVDS_A3_POWER_UP)
	 * appropriately here, but we need to look more thoroughly into how
	 * panels behave in the two modes.
	 */

	/* Set the dithering flag on LVDS as needed, note that there is no
	 * special lvds dither control bit on pch-split platforms, dithering is
	 * only controlled through the PIPECONF reg. */
	if (INTEL_INFO(dev)->gen == 4) {
		if (dev_priv->lvds_dither)
			temp |= LVDS_ENABLE_DITHER;
		else
			temp &= ~LVDS_ENABLE_DITHER;
	}
	temp &= ~(LVDS_HSYNC_POLARITY | LVDS_VSYNC_POLARITY);
	if (fixed_mode->flags & DRM_MODE_FLAG_NHSYNC)
		temp |= LVDS_HSYNC_POLARITY;
	if (fixed_mode->flags & DRM_MODE_FLAG_NVSYNC)
		temp |= LVDS_VSYNC_POLARITY;

	I915_WRITE(lvds_encoder->reg, temp);
}