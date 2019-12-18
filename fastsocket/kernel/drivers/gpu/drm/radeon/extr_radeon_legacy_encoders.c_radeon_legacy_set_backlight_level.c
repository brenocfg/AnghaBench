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
typedef  void* u8 ;
struct radeon_encoder_lvds {scalar_t__ backlight_level; int dpms_mode; } ;
struct radeon_encoder_atom_dig {scalar_t__ backlight_level; int dpms_mode; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; struct radeon_encoder_lvds* enc_priv; } ;
struct radeon_device {scalar_t__ is_atom_bios; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_OFF ; 
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  radeon_legacy_lvds_update (TYPE_1__*,int) ; 

void
radeon_legacy_set_backlight_level(struct radeon_encoder *radeon_encoder, u8 level)
{
	struct drm_device *dev = radeon_encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	int dpms_mode = DRM_MODE_DPMS_ON;

	if (radeon_encoder->enc_priv) {
		if (rdev->is_atom_bios) {
			struct radeon_encoder_atom_dig *lvds = radeon_encoder->enc_priv;
			if (lvds->backlight_level > 0)
				dpms_mode = lvds->dpms_mode;
			else
				dpms_mode = DRM_MODE_DPMS_OFF;
			lvds->backlight_level = level;
		} else {
			struct radeon_encoder_lvds *lvds = radeon_encoder->enc_priv;
			if (lvds->backlight_level > 0)
				dpms_mode = lvds->dpms_mode;
			else
				dpms_mode = DRM_MODE_DPMS_OFF;
			lvds->backlight_level = level;
		}
	}

	radeon_legacy_lvds_update(&radeon_encoder->base, dpms_mode);
}