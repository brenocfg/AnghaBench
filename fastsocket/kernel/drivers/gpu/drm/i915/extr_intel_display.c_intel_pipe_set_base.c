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
struct intel_crtc {scalar_t__ plane; int /*<<< orphan*/  pipe; } ;
struct TYPE_3__ {int (* update_plane ) (struct drm_crtc*,struct drm_framebuffer*,int,int) ;} ;
struct drm_i915_private {scalar_t__ num_pipe; TYPE_1__ display; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;
struct drm_crtc {int x; int y; struct drm_framebuffer* fb; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  intel_crtc_update_sarea_pos (struct drm_crtc*,int,int) ; 
 int /*<<< orphan*/  intel_finish_fb (struct drm_framebuffer*) ; 
 int intel_pin_and_fence_fb_obj (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_unpin_fb_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_update_fbc (struct drm_device*) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct drm_crtc*,struct drm_framebuffer*,int,int) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 TYPE_2__* to_intel_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static int
intel_pipe_set_base(struct drm_crtc *crtc, int x, int y,
		    struct drm_framebuffer *fb)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct drm_framebuffer *old_fb;
	int ret;

	/* no fb bound */
	if (!fb) {
		DRM_ERROR("No FB bound\n");
		return 0;
	}

	if(intel_crtc->plane > dev_priv->num_pipe) {
		DRM_ERROR("no plane for crtc: plane %d, num_pipes %d\n",
				intel_crtc->plane,
				dev_priv->num_pipe);
		return -EINVAL;
	}

	mutex_lock(&dev->struct_mutex);
	ret = intel_pin_and_fence_fb_obj(dev,
					 to_intel_framebuffer(fb)->obj,
					 NULL);
	if (ret != 0) {
		mutex_unlock(&dev->struct_mutex);
		DRM_ERROR("pin & fence failed\n");
		return ret;
	}

	if (crtc->fb)
		intel_finish_fb(crtc->fb);

	ret = dev_priv->display.update_plane(crtc, fb, x, y);
	if (ret) {
		intel_unpin_fb_obj(to_intel_framebuffer(fb)->obj);
		mutex_unlock(&dev->struct_mutex);
		DRM_ERROR("failed to update base address\n");
		return ret;
	}

	old_fb = crtc->fb;
	crtc->fb = fb;
	crtc->x = x;
	crtc->y = y;

	if (old_fb) {
		intel_wait_for_vblank(dev, intel_crtc->pipe);
		intel_unpin_fb_obj(to_intel_framebuffer(old_fb)->obj);
	}

	intel_update_fbc(dev);
	mutex_unlock(&dev->struct_mutex);

	intel_crtc_update_sarea_pos(crtc, x, y);

	return 0;
}