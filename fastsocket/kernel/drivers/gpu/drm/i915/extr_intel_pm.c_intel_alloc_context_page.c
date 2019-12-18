#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_i915_gem_object {int /*<<< orphan*/  base; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* i915_gem_alloc_object (struct drm_device*,int) ; 
 int i915_gem_object_pin (struct drm_i915_gem_object*,int,int,int) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_i915_gem_object *
intel_alloc_context_page(struct drm_device *dev)
{
	struct drm_i915_gem_object *ctx;
	int ret;

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));

	ctx = i915_gem_alloc_object(dev, 4096);
	if (!ctx) {
		DRM_DEBUG("failed to alloc power context, RC6 disabled\n");
		return NULL;
	}

	ret = i915_gem_object_pin(ctx, 4096, true, false);
	if (ret) {
		DRM_ERROR("failed to pin power context: %d\n", ret);
		goto err_unref;
	}

	ret = i915_gem_object_set_to_gtt_domain(ctx, 1);
	if (ret) {
		DRM_ERROR("failed to set-domain on power context: %d\n", ret);
		goto err_unpin;
	}

	return ctx;

err_unpin:
	i915_gem_object_unpin(ctx);
err_unref:
	drm_gem_object_unreference(&ctx->base);
	return NULL;
}