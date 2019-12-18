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
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE41 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE61 (struct radeon_device*) ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  EXTERNAL_ENCODER_ACTION_V3_DISABLE_OUTPUT ; 
 int /*<<< orphan*/  EXTERNAL_ENCODER_ACTION_V3_ENABLE_OUTPUT ; 
 int /*<<< orphan*/  EXTERNAL_ENCODER_ACTION_V3_ENCODER_BLANKING ; 
 int /*<<< orphan*/  EXTERNAL_ENCODER_ACTION_V3_ENCODER_BLANKING_OFF ; 
 int /*<<< orphan*/  atombios_external_encoder_setup (struct drm_encoder*,struct drm_encoder*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
radeon_atom_encoder_dpms_ext(struct drm_encoder *encoder,
			     struct drm_encoder *ext_encoder,
			     int mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
	default:
		if (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE61(rdev)) {
			atombios_external_encoder_setup(encoder, ext_encoder,
							EXTERNAL_ENCODER_ACTION_V3_ENABLE_OUTPUT);
			atombios_external_encoder_setup(encoder, ext_encoder,
							EXTERNAL_ENCODER_ACTION_V3_ENCODER_BLANKING_OFF);
		} else
			atombios_external_encoder_setup(encoder, ext_encoder, ATOM_ENABLE);
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		if (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE61(rdev)) {
			atombios_external_encoder_setup(encoder, ext_encoder,
							EXTERNAL_ENCODER_ACTION_V3_ENCODER_BLANKING);
			atombios_external_encoder_setup(encoder, ext_encoder,
							EXTERNAL_ENCODER_ACTION_V3_DISABLE_OUTPUT);
		} else
			atombios_external_encoder_setup(encoder, ext_encoder, ATOM_DISABLE);
		break;
	}
}