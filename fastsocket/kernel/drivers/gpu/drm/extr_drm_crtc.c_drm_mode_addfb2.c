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
struct drm_mode_fb_cmd2 {int flags; int fb_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_mode_config {TYPE_1__* funcs; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct TYPE_4__ {int id; } ;
struct drm_framebuffer {TYPE_2__ base; int /*<<< orphan*/  filp_head; } ;
struct drm_file {int /*<<< orphan*/  fbs_lock; int /*<<< orphan*/  fbs; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct TYPE_3__ {struct drm_framebuffer* (* fb_create ) (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int DRM_MODE_FB_INTERLACED ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 int PTR_ERR (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int framebuffer_check (struct drm_mode_fb_cmd2*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_framebuffer* stub1 (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2*) ; 

int drm_mode_addfb2(struct drm_device *dev,
		    void *data, struct drm_file *file_priv)
{
	struct drm_mode_fb_cmd2 *r = data;
	struct drm_mode_config *config = &dev->mode_config;
	struct drm_framebuffer *fb;
	int ret;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EINVAL;

	if (r->flags & ~DRM_MODE_FB_INTERLACED) {
		DRM_DEBUG_KMS("bad framebuffer flags 0x%08x\n", r->flags);
		return -EINVAL;
	}

	if ((config->min_width > r->width) || (r->width > config->max_width)) {
		DRM_DEBUG_KMS("bad framebuffer width %d, should be >= %d && <= %d\n",
			  r->width, config->min_width, config->max_width);
		return -EINVAL;
	}
	if ((config->min_height > r->height) || (r->height > config->max_height)) {
		DRM_DEBUG_KMS("bad framebuffer height %d, should be >= %d && <= %d\n",
			  r->height, config->min_height, config->max_height);
		return -EINVAL;
	}

	ret = framebuffer_check(r);
	if (ret)
		return ret;

	fb = dev->mode_config.funcs->fb_create(dev, file_priv, r);
	if (IS_ERR(fb)) {
		DRM_DEBUG_KMS("could not create framebuffer\n");
		return PTR_ERR(fb);
	}

	mutex_lock(&file_priv->fbs_lock);
	r->fb_id = fb->base.id;
	list_add(&fb->filp_head, &file_priv->fbs);
	DRM_DEBUG_KMS("[FB:%d]\n", fb->base.id);
	mutex_unlock(&file_priv->fbs_lock);


	return ret;
}