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
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int EIO ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_context_init (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_init_ppgtt (struct drm_device*) ; 
 int i915_gem_init_rings (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_init_swizzling (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_l3_remap (struct drm_device*) ; 
 int /*<<< orphan*/  intel_enable_gtt () ; 

int
i915_gem_init_hw(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	if (INTEL_INFO(dev)->gen < 6 && !intel_enable_gtt())
		return -EIO;

	if (IS_HASWELL(dev) && (I915_READ(0x120010) == 1))
		I915_WRITE(0x9008, I915_READ(0x9008) | 0xf0000);

	i915_gem_l3_remap(dev);

	i915_gem_init_swizzling(dev);

	ret = i915_gem_init_rings(dev);
	if (ret)
		return ret;

	/*
	 * XXX: There was some w/a described somewhere suggesting loading
	 * contexts before PPGTT.
	 */
	i915_gem_context_init(dev);
	i915_gem_init_ppgtt(dev);

	return 0;
}