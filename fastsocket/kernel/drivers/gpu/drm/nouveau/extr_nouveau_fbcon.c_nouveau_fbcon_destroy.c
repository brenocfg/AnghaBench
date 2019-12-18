#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nouveau_framebuffer {int /*<<< orphan*/  base; TYPE_1__* nvbo; int /*<<< orphan*/  vma; } ;
struct TYPE_7__ {struct fb_info* fbdev; } ;
struct nouveau_fbdev {TYPE_4__ helper; struct nouveau_framebuffer nouveau_fb; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct fb_info {TYPE_3__ cmap; } ;
struct drm_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  gem; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_3__*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (TYPE_1__*) ; 
 int /*<<< orphan*/  nouveau_bo_vma_del (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int
nouveau_fbcon_destroy(struct drm_device *dev, struct nouveau_fbdev *fbcon)
{
	struct nouveau_framebuffer *nouveau_fb = &fbcon->nouveau_fb;
	struct fb_info *info;

	if (fbcon->helper.fbdev) {
		info = fbcon->helper.fbdev;
		unregister_framebuffer(info);
		if (info->cmap.len)
			fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
	}

	if (nouveau_fb->nvbo) {
		nouveau_bo_unmap(nouveau_fb->nvbo);
		nouveau_bo_vma_del(nouveau_fb->nvbo, &nouveau_fb->vma);
		drm_gem_object_unreference_unlocked(nouveau_fb->nvbo->gem);
		nouveau_fb->nvbo = NULL;
	}
	drm_fb_helper_fini(&fbcon->helper);
	drm_framebuffer_unregister_private(&nouveau_fb->base);
	drm_framebuffer_cleanup(&nouveau_fb->base);
	return 0;
}