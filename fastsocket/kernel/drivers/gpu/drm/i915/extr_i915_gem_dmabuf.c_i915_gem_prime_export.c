#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 struct dma_buf* dma_buf_export (struct drm_i915_gem_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_dmabuf_ops ; 
 struct drm_i915_gem_object* to_intel_bo (struct drm_gem_object*) ; 

struct dma_buf *i915_gem_prime_export(struct drm_device *dev,
				      struct drm_gem_object *gem_obj, int flags)
{
	struct drm_i915_gem_object *obj = to_intel_bo(gem_obj);

	return dma_buf_export(obj, &i915_dmabuf_ops, obj->base.size, flags);
}