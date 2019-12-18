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
struct drm_display_mode {unsigned int htotal; unsigned int hdisplay; unsigned int vtotal; unsigned int vdisplay; unsigned int hsync_start; unsigned int vsync_start; unsigned int hsync_end; unsigned int vsync_end; unsigned int crtc_hdisplay; unsigned int crtc_vdisplay; unsigned int crtc_htotal; unsigned int crtc_hsync_start; unsigned int crtc_hsync_end; unsigned int crtc_vtotal; unsigned int crtc_vsync_start; unsigned int crtc_vsync_end; int /*<<< orphan*/  flags; int /*<<< orphan*/  clock; } ;
struct radeon_encoder {struct drm_display_mode native_mode; } ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 int /*<<< orphan*/  CRTC_INTERLACE_HALVE_V ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void radeon_panel_mode_fixup(struct drm_encoder *encoder,
			     struct drm_display_mode *adjusted_mode)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct drm_display_mode *native_mode = &radeon_encoder->native_mode;
	unsigned hblank = native_mode->htotal - native_mode->hdisplay;
	unsigned vblank = native_mode->vtotal - native_mode->vdisplay;
	unsigned hover = native_mode->hsync_start - native_mode->hdisplay;
	unsigned vover = native_mode->vsync_start - native_mode->vdisplay;
	unsigned hsync_width = native_mode->hsync_end - native_mode->hsync_start;
	unsigned vsync_width = native_mode->vsync_end - native_mode->vsync_start;

	adjusted_mode->clock = native_mode->clock;
	adjusted_mode->flags = native_mode->flags;

	if (ASIC_IS_AVIVO(rdev)) {
		adjusted_mode->hdisplay = native_mode->hdisplay;
		adjusted_mode->vdisplay = native_mode->vdisplay;
	}

	adjusted_mode->htotal = native_mode->hdisplay + hblank;
	adjusted_mode->hsync_start = native_mode->hdisplay + hover;
	adjusted_mode->hsync_end = adjusted_mode->hsync_start + hsync_width;

	adjusted_mode->vtotal = native_mode->vdisplay + vblank;
	adjusted_mode->vsync_start = native_mode->vdisplay + vover;
	adjusted_mode->vsync_end = adjusted_mode->vsync_start + vsync_width;

	drm_mode_set_crtcinfo(adjusted_mode, CRTC_INTERLACE_HALVE_V);

	if (ASIC_IS_AVIVO(rdev)) {
		adjusted_mode->crtc_hdisplay = native_mode->hdisplay;
		adjusted_mode->crtc_vdisplay = native_mode->vdisplay;
	}

	adjusted_mode->crtc_htotal = adjusted_mode->crtc_hdisplay + hblank;
	adjusted_mode->crtc_hsync_start = adjusted_mode->crtc_hdisplay + hover;
	adjusted_mode->crtc_hsync_end = adjusted_mode->crtc_hsync_start + hsync_width;

	adjusted_mode->crtc_vtotal = adjusted_mode->crtc_vdisplay + vblank;
	adjusted_mode->crtc_vsync_start = adjusted_mode->crtc_vdisplay + vover;
	adjusted_mode->crtc_vsync_end = adjusted_mode->crtc_vsync_start + vsync_width;

}