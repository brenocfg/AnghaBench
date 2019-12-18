#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_framebuffer {int /*<<< orphan*/  base; int /*<<< orphan*/ * obj; } ;
struct TYPE_4__ {struct fb_info* fbdev; } ;
struct radeon_fbdev {TYPE_2__ helper; struct radeon_framebuffer rfb; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct fb_info {TYPE_1__ cmap; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_1__*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  radeonfb_destroy_pinned_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int radeon_fbdev_destroy(struct drm_device *dev, struct radeon_fbdev *rfbdev)
{
	struct fb_info *info;
	struct radeon_framebuffer *rfb = &rfbdev->rfb;

	if (rfbdev->helper.fbdev) {
		info = rfbdev->helper.fbdev;

		unregister_framebuffer(info);
		if (info->cmap.len)
			fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
	}

	if (rfb->obj) {
		radeonfb_destroy_pinned_object(rfb->obj);
		rfb->obj = NULL;
	}
	drm_fb_helper_fini(&rfbdev->helper);
	drm_framebuffer_unregister_private(&rfb->base);
	drm_framebuffer_cleanup(&rfb->base);

	return 0;
}