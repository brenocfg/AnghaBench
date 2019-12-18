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
struct TYPE_2__ {int read_domains; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int I915_GEM_GPU_DOMAINS ; 
 int i915_gem_object_wait_rendering (struct drm_i915_gem_object*,int) ; 

int
i915_gem_object_finish_gpu(struct drm_i915_gem_object *obj)
{
	int ret;

	if ((obj->base.read_domains & I915_GEM_GPU_DOMAINS) == 0)
		return 0;

	ret = i915_gem_object_wait_rendering(obj, false);
	if (ret)
		return ret;

	/* Ensure that we invalidate the GPU's caches and TLBs. */
	obj->base.read_domains &= ~I915_GEM_GPU_DOMAINS;
	return 0;
}