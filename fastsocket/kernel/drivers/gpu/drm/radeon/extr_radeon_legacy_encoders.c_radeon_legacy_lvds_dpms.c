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
struct radeon_encoder_lvds {int dpms_mode; } ;
struct radeon_encoder_atom_dig {int dpms_mode; } ;
struct radeon_encoder {struct radeon_encoder_lvds* enc_priv; } ;
struct radeon_device {scalar_t__ is_atom_bios; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  radeon_legacy_lvds_update (struct drm_encoder*,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void radeon_legacy_lvds_dpms(struct drm_encoder *encoder, int mode)
{
	struct radeon_device *rdev = encoder->dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	DRM_DEBUG("\n");

	if (radeon_encoder->enc_priv) {
		if (rdev->is_atom_bios) {
			struct radeon_encoder_atom_dig *lvds = radeon_encoder->enc_priv;
			lvds->dpms_mode = mode;
		} else {
			struct radeon_encoder_lvds *lvds = radeon_encoder->enc_priv;
			lvds->dpms_mode = mode;
		}
	}

	radeon_legacy_lvds_update(encoder, mode);
}