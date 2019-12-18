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
typedef  int u32 ;
struct intel_ring_buffer {int dummy; } ;
struct TYPE_3__ {int interruptible; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
struct drm_i915_gem_object {int tiling_mode; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
#define  I915_TILING_NONE 130 
#define  I915_TILING_X 129 
#define  I915_TILING_Y 128 
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  IS_BROADWATER (struct drm_device*) ; 
 int /*<<< orphan*/  IS_CRESTLINE (struct drm_device*) ; 
 int i915_gem_object_get_fence (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_pin_fence (struct drm_i915_gem_object*) ; 
 int i915_gem_object_pin_to_display_plane (struct drm_i915_gem_object*,int,struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (struct drm_i915_gem_object*) ; 

int
intel_pin_and_fence_fb_obj(struct drm_device *dev,
			   struct drm_i915_gem_object *obj,
			   struct intel_ring_buffer *pipelined)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 alignment;
	int ret;

	switch (obj->tiling_mode) {
	case I915_TILING_NONE:
		if (IS_BROADWATER(dev) || IS_CRESTLINE(dev))
			alignment = 128 * 1024;
		else if (INTEL_INFO(dev)->gen >= 4)
			alignment = 4 * 1024;
		else
			alignment = 64 * 1024;
		break;
	case I915_TILING_X:
		/* pin() will align the object as required by fence */
		alignment = 0;
		break;
	case I915_TILING_Y:
		/* FIXME: Is this true? */
		DRM_ERROR("Y tiled not allowed for scan out buffers\n");
		return -EINVAL;
	default:
		BUG();
	}

	dev_priv->mm.interruptible = false;
	ret = i915_gem_object_pin_to_display_plane(obj, alignment, pipelined);
	if (ret)
		goto err_interruptible;

	/* Install a fence for tiled scan-out. Pre-i965 always needs a
	 * fence, whereas 965+ only requires a fence if using
	 * framebuffer compression.  For simplicity, we always install
	 * a fence as the cost is not that onerous.
	 */
	ret = i915_gem_object_get_fence(obj);
	if (ret)
		goto err_unpin;

	i915_gem_object_pin_fence(obj);

	dev_priv->mm.interruptible = true;
	return 0;

err_unpin:
	i915_gem_object_unpin(obj);
err_interruptible:
	dev_priv->mm.interruptible = true;
	return ret;
}