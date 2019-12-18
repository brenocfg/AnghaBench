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
struct radeon_encoder_atom_dac {scalar_t__ tv_std; } ;
struct radeon_encoder {int active_device; struct radeon_encoder_atom_dac* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_display_mode {int flags; scalar_t__ crtc_vsync_start; scalar_t__ crtc_vdisplay; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE3 (struct radeon_device*) ; 
 int ATOM_DEVICE_DFP_SUPPORT ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 scalar_t__ TV_STD_NTSC ; 
 scalar_t__ TV_STD_NTSC_J ; 
 scalar_t__ TV_STD_PAL_M ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atom_get_tv_timings (struct radeon_device*,int,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_dp_set_link_config (struct drm_connector*,struct drm_display_mode*) ; 
 scalar_t__ radeon_encoder_get_dp_bridge_encoder_id (struct drm_encoder*) ; 
 int /*<<< orphan*/  radeon_encoder_set_active_device (struct drm_encoder*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  radeon_panel_mode_fixup (struct drm_encoder*,struct drm_display_mode*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static bool radeon_atom_mode_fixup(struct drm_encoder *encoder,
				   const struct drm_display_mode *mode,
				   struct drm_display_mode *adjusted_mode)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;

	/* set the active encoder to connector routing */
	radeon_encoder_set_active_device(encoder);
	drm_mode_set_crtcinfo(adjusted_mode, 0);

	/* hw bug */
	if ((mode->flags & DRM_MODE_FLAG_INTERLACE)
	    && (mode->crtc_vsync_start < (mode->crtc_vdisplay + 2)))
		adjusted_mode->crtc_vsync_start = adjusted_mode->crtc_vdisplay + 2;

	/* get the native mode for LVDS */
	if (radeon_encoder->active_device & (ATOM_DEVICE_LCD_SUPPORT))
		radeon_panel_mode_fixup(encoder, adjusted_mode);

	/* get the native mode for TV */
	if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT)) {
		struct radeon_encoder_atom_dac *tv_dac = radeon_encoder->enc_priv;
		if (tv_dac) {
			if (tv_dac->tv_std == TV_STD_NTSC ||
			    tv_dac->tv_std == TV_STD_NTSC_J ||
			    tv_dac->tv_std == TV_STD_PAL_M)
				radeon_atom_get_tv_timings(rdev, 0, adjusted_mode);
			else
				radeon_atom_get_tv_timings(rdev, 1, adjusted_mode);
		}
	}

	if (ASIC_IS_DCE3(rdev) &&
	    ((radeon_encoder->active_device & (ATOM_DEVICE_DFP_SUPPORT | ATOM_DEVICE_LCD_SUPPORT)) ||
	     (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE))) {
		struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
		radeon_dp_set_link_config(connector, adjusted_mode);
	}

	return true;
}