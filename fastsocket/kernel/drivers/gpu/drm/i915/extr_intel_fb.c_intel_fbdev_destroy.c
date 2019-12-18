#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_framebuffer {TYPE_1__* obj; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {struct fb_info* fbdev; } ;
struct intel_fbdev {TYPE_3__ helper; struct intel_framebuffer ifb; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct fb_info {TYPE_2__ cmap; int /*<<< orphan*/  screen_base; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_2__*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void intel_fbdev_destroy(struct drm_device *dev,
				struct intel_fbdev *ifbdev)
{
	struct fb_info *info;
	struct intel_framebuffer *ifb = &ifbdev->ifb;

	if (ifbdev->helper.fbdev) {
		info = ifbdev->helper.fbdev;
		unregister_framebuffer(info);
		iounmap(info->screen_base);
		if (info->cmap.len)
			fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
	}

	drm_fb_helper_fini(&ifbdev->helper);

	drm_framebuffer_unregister_private(&ifb->base);
	drm_framebuffer_cleanup(&ifb->base);
	if (ifb->obj) {
		drm_gem_object_unreference_unlocked(&ifb->obj->base);
		ifb->obj = NULL;
	}
}