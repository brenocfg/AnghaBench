#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct intel_crtc {scalar_t__ pipe; int cursor_addr; int cursor_width; int cursor_height; struct drm_i915_gem_object* cursor_bo; } ;
struct drm_i915_private {TYPE_3__* info; } ;
struct TYPE_9__ {int size; } ;
struct drm_i915_gem_object {int gtt_offset; TYPE_4__ base; TYPE_2__* phys_obj; scalar_t__ tiling_mode; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_8__ {scalar_t__ cursor_needs_physical; } ;
struct TYPE_7__ {TYPE_1__* handle; } ;
struct TYPE_6__ {int busaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSIZE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I915_GEM_PHYS_CURSOR_0 ; 
 int /*<<< orphan*/  I915_GEM_PHYS_CURSOR_1 ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_I830 (struct drm_device*) ; 
 int /*<<< orphan*/  drm_gem_object_lookup (struct drm_device*,struct drm_file*,int) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (TYPE_4__*) ; 
 int i915_gem_attach_phys_object (struct drm_device*,struct drm_i915_gem_object*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_gem_detach_phys_object (struct drm_device*,struct drm_i915_gem_object*) ; 
 int i915_gem_object_pin_to_display_plane (struct drm_i915_gem_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i915_gem_object_put_fence (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  intel_crtc_update_cursor (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* to_intel_bo (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int intel_crtc_cursor_set(struct drm_crtc *crtc,
				 struct drm_file *file,
				 uint32_t handle,
				 uint32_t width, uint32_t height)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct drm_i915_gem_object *obj;
	uint32_t addr;
	int ret;

	/* if we want to turn off the cursor ignore width and height */
	if (!handle) {
		DRM_DEBUG_KMS("cursor off\n");
		addr = 0;
		obj = NULL;
		mutex_lock(&dev->struct_mutex);
		goto finish;
	}

	/* Currently we only support 64x64 cursors */
	if (width != 64 || height != 64) {
		DRM_ERROR("we currently only support 64x64 cursors\n");
		return -EINVAL;
	}

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, handle));
	if (&obj->base == NULL)
		return -ENOENT;

	if (obj->base.size < width * height * 4) {
		DRM_ERROR("buffer is to small\n");
		ret = -ENOMEM;
		goto fail;
	}

	/* we only need to pin inside GTT if cursor is non-phy */
	mutex_lock(&dev->struct_mutex);
	if (!dev_priv->info->cursor_needs_physical) {
		if (obj->tiling_mode) {
			DRM_ERROR("cursor cannot be tiled\n");
			ret = -EINVAL;
			goto fail_locked;
		}

		ret = i915_gem_object_pin_to_display_plane(obj, 0, NULL);
		if (ret) {
			DRM_ERROR("failed to move cursor bo into the GTT\n");
			goto fail_locked;
		}

		ret = i915_gem_object_put_fence(obj);
		if (ret) {
			DRM_ERROR("failed to release fence for cursor");
			goto fail_unpin;
		}

		addr = obj->gtt_offset;
	} else {
		int align = IS_I830(dev) ? 16 * 1024 : 256;
		ret = i915_gem_attach_phys_object(dev, obj,
						  (intel_crtc->pipe == 0) ? I915_GEM_PHYS_CURSOR_0 : I915_GEM_PHYS_CURSOR_1,
						  align);
		if (ret) {
			DRM_ERROR("failed to attach phys object\n");
			goto fail_locked;
		}
		addr = obj->phys_obj->handle->busaddr;
	}

	if (IS_GEN2(dev))
		I915_WRITE(CURSIZE, (height << 12) | width);

 finish:
	if (intel_crtc->cursor_bo) {
		if (dev_priv->info->cursor_needs_physical) {
			if (intel_crtc->cursor_bo != obj)
				i915_gem_detach_phys_object(dev, intel_crtc->cursor_bo);
		} else
			i915_gem_object_unpin(intel_crtc->cursor_bo);
		drm_gem_object_unreference(&intel_crtc->cursor_bo->base);
	}

	mutex_unlock(&dev->struct_mutex);

	intel_crtc->cursor_addr = addr;
	intel_crtc->cursor_bo = obj;
	intel_crtc->cursor_width = width;
	intel_crtc->cursor_height = height;

	intel_crtc_update_cursor(crtc, true);

	return 0;
fail_unpin:
	i915_gem_object_unpin(obj);
fail_locked:
	mutex_unlock(&dev->struct_mutex);
fail:
	drm_gem_object_unreference_unlocked(&obj->base);
	return ret;
}