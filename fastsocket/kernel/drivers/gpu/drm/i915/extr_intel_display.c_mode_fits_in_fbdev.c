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
struct drm_i915_private {TYPE_2__* fbdev; } ;
struct TYPE_6__ {int size; } ;
struct drm_i915_gem_object {TYPE_3__ base; } ;
struct drm_framebuffer {int* pitches; int /*<<< orphan*/  bits_per_pixel; } ;
struct drm_display_mode {int vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {struct drm_framebuffer base; struct drm_i915_gem_object* obj; } ;
struct TYPE_5__ {TYPE_1__ ifb; } ;

/* Variables and functions */
 int intel_framebuffer_pitch_for_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_framebuffer *
mode_fits_in_fbdev(struct drm_device *dev,
		   struct drm_display_mode *mode)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;
	struct drm_framebuffer *fb;

	if (dev_priv->fbdev == NULL)
		return NULL;

	obj = dev_priv->fbdev->ifb.obj;
	if (obj == NULL)
		return NULL;

	fb = &dev_priv->fbdev->ifb.base;
	if (fb->pitches[0] < intel_framebuffer_pitch_for_width(mode->hdisplay,
							       fb->bits_per_pixel))
		return NULL;

	if (obj->base.size < mode->vdisplay * fb->pitches[0])
		return NULL;

	return fb;
}