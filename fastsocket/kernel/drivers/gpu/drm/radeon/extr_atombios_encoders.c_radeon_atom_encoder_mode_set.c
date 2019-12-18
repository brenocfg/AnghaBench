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
struct radeon_encoder {int active_device; int encoder_id; int devices; int /*<<< orphan*/  pixel_clock; } ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 scalar_t__ ATOM_ENCODER_MODE_HDMI ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC1 142 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC2 141 
#define  ENCODER_OBJECT_ID_INTERNAL_DDI 140 
#define  ENCODER_OBJECT_ID_INTERNAL_DVO1 139 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1 138 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2 137 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 136 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 135 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1 134 
#define  ENCODER_OBJECT_ID_INTERNAL_LVDS 133 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 132 
#define  ENCODER_OBJECT_ID_INTERNAL_TMDS1 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 128 
 int /*<<< orphan*/  PANEL_ENCODER_ACTION_ENABLE ; 
 int /*<<< orphan*/  atombios_apply_encoder_quirks (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  atombios_dac_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_digital_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_dvo_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 scalar_t__ atombios_get_encoder_mode (struct drm_encoder*) ; 
 int /*<<< orphan*/  atombios_tv_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_yuv_setup (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  evergreen_hdmi_setmode (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  r600_hdmi_enable (struct drm_encoder*) ; 
 int /*<<< orphan*/  r600_hdmi_setmode (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_atom_encoder_dpms (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
radeon_atom_encoder_mode_set(struct drm_encoder *encoder,
			     struct drm_display_mode *mode,
			     struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	radeon_encoder->pixel_clock = adjusted_mode->clock;

	/* need to call this here rather than in prepare() since we need some crtc info */
	radeon_atom_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	if (ASIC_IS_AVIVO(rdev) && !ASIC_IS_DCE4(rdev)) {
		if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT | ATOM_DEVICE_TV_SUPPORT))
			atombios_yuv_setup(encoder, true);
		else
			atombios_yuv_setup(encoder, false);
	}

	switch (radeon_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
	case ENCODER_OBJECT_ID_INTERNAL_LVDS:
	case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		atombios_digital_setup(encoder, PANEL_ENCODER_ACTION_ENABLE);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		/* handled in dpms */
		break;
	case ENCODER_OBJECT_ID_INTERNAL_DDI:
	case ENCODER_OBJECT_ID_INTERNAL_DVO1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		atombios_dvo_setup(encoder, ATOM_ENABLE);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_DAC1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
	case ENCODER_OBJECT_ID_INTERNAL_DAC2:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		atombios_dac_setup(encoder, ATOM_ENABLE);
		if (radeon_encoder->devices & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT)) {
			if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT))
				atombios_tv_setup(encoder, ATOM_ENABLE);
			else
				atombios_tv_setup(encoder, ATOM_DISABLE);
		}
		break;
	}

	atombios_apply_encoder_quirks(encoder, adjusted_mode);

	if (atombios_get_encoder_mode(encoder) == ATOM_ENCODER_MODE_HDMI) {
		r600_hdmi_enable(encoder);
		if (ASIC_IS_DCE6(rdev))
			; /* TODO (use pointers instead of if-s?) */
		else if (ASIC_IS_DCE4(rdev))
			evergreen_hdmi_setmode(encoder, adjusted_mode);
		else
			r600_hdmi_setmode(encoder, adjusted_mode);
	}
}