#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct fb_info* fbdev; struct drm_framebuffer* fb; } ;
struct drm_framebuffer {unsigned long* pitches; unsigned long depth; } ;
struct TYPE_11__ {struct drm_framebuffer base; } ;
struct radeon_fbdev {TYPE_6__ helper; TYPE_5__ rfb; struct radeon_device* rdev; } ;
struct TYPE_9__ {unsigned long vram_start; unsigned long aper_base; } ;
struct radeon_device {TYPE_4__* ddev; TYPE_3__ mc; TYPE_1__* pdev; } ;
struct radeon_bo {int /*<<< orphan*/ * kptr; } ;
struct TYPE_8__ {unsigned long smem_start; void* smem_len; int /*<<< orphan*/  id; } ;
struct fb_info {int flags; TYPE_2__ fix; int /*<<< orphan*/  cmap; int /*<<< orphan*/ * screen_base; void* screen_size; int /*<<< orphan*/ * fbops; struct radeon_fbdev* par; } ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_gem_object {int dummy; } ;
struct drm_fb_helper_surface_size {int surface_bpp; int /*<<< orphan*/  fb_height; int /*<<< orphan*/  fb_width; int /*<<< orphan*/  surface_depth; int /*<<< orphan*/  surface_height; int /*<<< orphan*/  surface_width; } ;
struct drm_fb_helper {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned long) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int FBINFO_CAN_FORCE_OUTPUT ; 
 int FBINFO_DEFAULT ; 
 int /*<<< orphan*/  drm_fb_helper_fill_fix (struct fb_info*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  drm_fb_helper_fill_var (struct fb_info*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_mode_legacy_fb_format (int,int /*<<< orphan*/ ) ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct fb_info* framebuffer_alloc (int /*<<< orphan*/ ,struct device*) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ *,int,void*) ; 
 unsigned long radeon_bo_gpu_offset (struct radeon_bo*) ; 
 void* radeon_bo_size (struct radeon_bo*) ; 
 int radeon_framebuffer_init (TYPE_4__*,TYPE_5__*,struct drm_mode_fb_cmd2*,struct drm_gem_object*) ; 
 int radeonfb_create_pinned_object (struct radeon_fbdev*,struct drm_mode_fb_cmd2*,struct drm_gem_object**) ; 
 int /*<<< orphan*/  radeonfb_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vga_switcheroo_client_fb_set (int /*<<< orphan*/ ,struct fb_info*) ; 

__attribute__((used)) static int radeonfb_create(struct drm_fb_helper *helper,
			   struct drm_fb_helper_surface_size *sizes)
{
	struct radeon_fbdev *rfbdev = (struct radeon_fbdev *)helper;
	struct radeon_device *rdev = rfbdev->rdev;
	struct fb_info *info;
	struct drm_framebuffer *fb = NULL;
	struct drm_mode_fb_cmd2 mode_cmd;
	struct drm_gem_object *gobj = NULL;
	struct radeon_bo *rbo = NULL;
	struct device *device = &rdev->pdev->dev;
	int ret;
	unsigned long tmp;

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;

	/* avivo can't scanout real 24bpp */
	if ((sizes->surface_bpp == 24) && ASIC_IS_AVIVO(rdev))
		sizes->surface_bpp = 32;

	mode_cmd.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
							  sizes->surface_depth);

	ret = radeonfb_create_pinned_object(rfbdev, &mode_cmd, &gobj);
	if (ret) {
		DRM_ERROR("failed to create fbcon object %d\n", ret);
		return ret;
	}

	rbo = gem_to_radeon_bo(gobj);

	/* okay we have an object now allocate the framebuffer */
	info = framebuffer_alloc(0, device);
	if (info == NULL) {
		ret = -ENOMEM;
		goto out_unref;
	}

	info->par = rfbdev;

	ret = radeon_framebuffer_init(rdev->ddev, &rfbdev->rfb, &mode_cmd, gobj);
	if (ret) {
		DRM_ERROR("failed to initalise framebuffer %d\n", ret);
		goto out_unref;
	}

	fb = &rfbdev->rfb.base;

	/* setup helper */
	rfbdev->helper.fb = fb;
	rfbdev->helper.fbdev = info;

	memset_io(rbo->kptr, 0x0, radeon_bo_size(rbo));

	strcpy(info->fix.id, "radeondrmfb");

	drm_fb_helper_fill_fix(info, fb->pitches[0], fb->depth);

	info->flags = FBINFO_DEFAULT | FBINFO_CAN_FORCE_OUTPUT;
	info->fbops = &radeonfb_ops;

	tmp = radeon_bo_gpu_offset(rbo) - rdev->mc.vram_start;
	info->fix.smem_start = rdev->mc.aper_base + tmp;
	info->fix.smem_len = radeon_bo_size(rbo);
	info->screen_base = rbo->kptr;
	info->screen_size = radeon_bo_size(rbo);

	drm_fb_helper_fill_var(info, &rfbdev->helper, sizes->fb_width, sizes->fb_height);

	/* Use default scratch pixmap (info->pixmap.flags = FB_PIXMAP_SYSTEM) */

	if (info->screen_base == NULL) {
		ret = -ENOSPC;
		goto out_unref;
	}

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	if (ret) {
		ret = -ENOMEM;
		goto out_unref;
	}

	DRM_INFO("fb mappable at 0x%lX\n",  info->fix.smem_start);
	DRM_INFO("vram apper at 0x%lX\n",  (unsigned long)rdev->mc.aper_base);
	DRM_INFO("size %lu\n", (unsigned long)radeon_bo_size(rbo));
	DRM_INFO("fb depth is %d\n", fb->depth);
	DRM_INFO("   pitch is %d\n", fb->pitches[0]);

	vga_switcheroo_client_fb_set(rdev->ddev->pdev, info);
	return 0;

out_unref:
	if (rbo) {

	}
	if (fb && ret) {
		drm_gem_object_unreference(gobj);
		drm_framebuffer_unregister_private(fb);
		drm_framebuffer_cleanup(fb);
		kfree(fb);
	}
	return ret;
}