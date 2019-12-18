#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * funcs; } ;
struct radeon_fbdev {TYPE_3__ helper; struct radeon_device* rdev; } ;
struct TYPE_7__ {struct radeon_fbdev* rfbdev; } ;
struct TYPE_6__ {int real_vram_size; } ;
struct radeon_device {int /*<<< orphan*/  ddev; int /*<<< orphan*/  num_crtc; TYPE_2__ mode_info; TYPE_1__ mc; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_RN50 (struct radeon_device*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADEONFB_CONN_LIMIT ; 
 int drm_fb_helper_init (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_initial_config (TYPE_3__*,int) ; 
 int /*<<< orphan*/  drm_fb_helper_single_add_all_connectors (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct radeon_fbdev*) ; 
 struct radeon_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_fb_helper_funcs ; 

int radeon_fbdev_init(struct radeon_device *rdev)
{
	struct radeon_fbdev *rfbdev;
	int bpp_sel = 32;
	int ret;

	/* select 8 bpp console on RN50 or 16MB cards */
	if (ASIC_IS_RN50(rdev) || rdev->mc.real_vram_size <= (32*1024*1024))
		bpp_sel = 8;

	rfbdev = kzalloc(sizeof(struct radeon_fbdev), GFP_KERNEL);
	if (!rfbdev)
		return -ENOMEM;

	rfbdev->rdev = rdev;
	rdev->mode_info.rfbdev = rfbdev;
	rfbdev->helper.funcs = &radeon_fb_helper_funcs;

	ret = drm_fb_helper_init(rdev->ddev, &rfbdev->helper,
				 rdev->num_crtc,
				 RADEONFB_CONN_LIMIT);
	if (ret) {
		kfree(rfbdev);
		return ret;
	}

	drm_fb_helper_single_add_all_connectors(&rfbdev->helper);

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(rdev->ddev);

	drm_fb_helper_initial_config(&rfbdev->helper, bpp_sel);
	return 0;
}