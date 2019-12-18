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
struct TYPE_3__ {int /*<<< orphan*/  gtt_space; } ;
struct TYPE_4__ {unsigned long total; unsigned long mappable_end; } ;
struct drm_i915_private {TYPE_1__ mm; TYPE_2__ gtt; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ HAS_ALIASING_PPGTT (struct drm_device*) ; 
 unsigned long I915_PPGTT_PD_ENTRIES ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int i915_gem_init_aliasing_ppgtt (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_setup_global_gtt (struct drm_device*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ intel_enable_ppgtt (struct drm_device*) ; 

void i915_gem_init_global_gtt(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	unsigned long gtt_size, mappable_size;

	gtt_size = dev_priv->gtt.total;
	mappable_size = dev_priv->gtt.mappable_end;

	if (intel_enable_ppgtt(dev) && HAS_ALIASING_PPGTT(dev)) {
		int ret;
		/* PPGTT pdes are stolen from global gtt ptes, so shrink the
		 * aperture accordingly when using aliasing ppgtt. */
		gtt_size -= I915_PPGTT_PD_ENTRIES*PAGE_SIZE;

		i915_gem_setup_global_gtt(dev, 0, mappable_size, gtt_size);

		ret = i915_gem_init_aliasing_ppgtt(dev);
		if (!ret)
			return;

		DRM_ERROR("Aliased PPGTT setup failed %d\n", ret);
		drm_mm_takedown(&dev_priv->mm.gtt_space);
		gtt_size += I915_PPGTT_PD_ENTRIES*PAGE_SIZE;
	}
	i915_gem_setup_global_gtt(dev, 0, mappable_size, gtt_size);
}