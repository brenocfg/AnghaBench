#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  aper_base; } ;
struct TYPE_8__ {int mode_config_initialized; } ;
struct radeon_device {int num_crtc; TYPE_4__* ddev; scalar_t__ is_atom_bios; TYPE_3__ mc; TYPE_1__ mode_info; } ;
struct TYPE_9__ {int max_width; int max_height; int preferred_depth; int prefer_shadow; int /*<<< orphan*/  fb_base; int /*<<< orphan*/ * funcs; } ;
struct TYPE_11__ {TYPE_2__ mode_config; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_mode_config_init (TYPE_4__*) ; 
 int /*<<< orphan*/  radeon_afmt_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_atom_disp_eng_pll_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_atom_encoder_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_combios_check_hardcoded_edid (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_crtc_init (TYPE_4__*,int) ; 
 int /*<<< orphan*/  radeon_fbdev_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_hpd_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_i2c_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_mode_funcs ; 
 int radeon_modeset_create_props (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_init (struct radeon_device*) ; 
 int radeon_setup_enc_conn (TYPE_4__*) ; 

int radeon_modeset_init(struct radeon_device *rdev)
{
	int i;
	int ret;

	drm_mode_config_init(rdev->ddev);
	rdev->mode_info.mode_config_initialized = true;

	rdev->ddev->mode_config.funcs = &radeon_mode_funcs;

	if (ASIC_IS_DCE5(rdev)) {
		rdev->ddev->mode_config.max_width = 16384;
		rdev->ddev->mode_config.max_height = 16384;
	} else if (ASIC_IS_AVIVO(rdev)) {
		rdev->ddev->mode_config.max_width = 8192;
		rdev->ddev->mode_config.max_height = 8192;
	} else {
		rdev->ddev->mode_config.max_width = 4096;
		rdev->ddev->mode_config.max_height = 4096;
	}

	rdev->ddev->mode_config.preferred_depth = 24;
	rdev->ddev->mode_config.prefer_shadow = 1;

	rdev->ddev->mode_config.fb_base = rdev->mc.aper_base;

	ret = radeon_modeset_create_props(rdev);
	if (ret) {
		return ret;
	}

	/* init i2c buses */
	radeon_i2c_init(rdev);

	/* check combios for a valid hardcoded EDID - Sun servers */
	if (!rdev->is_atom_bios) {
		/* check for hardcoded EDID in BIOS */
		radeon_combios_check_hardcoded_edid(rdev);
	}

	/* allocate crtcs */
	for (i = 0; i < rdev->num_crtc; i++) {
		radeon_crtc_init(rdev->ddev, i);
	}

	/* okay we should have all the bios connectors */
	ret = radeon_setup_enc_conn(rdev->ddev);
	if (!ret) {
		return ret;
	}

	/* init dig PHYs, disp eng pll */
	if (rdev->is_atom_bios) {
		radeon_atom_encoder_init(rdev);
		radeon_atom_disp_eng_pll_init(rdev);
	}

	/* initialize hpd */
	radeon_hpd_init(rdev);

	/* setup afmt */
	radeon_afmt_init(rdev);

	/* Initialize power management */
	radeon_pm_init(rdev);

	radeon_fbdev_init(rdev);
	drm_kms_helper_poll_init(rdev->ddev);

	return 0;
}