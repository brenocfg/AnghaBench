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
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {int gtt_offset; TYPE_1__* gtt_space; TYPE_2__ base; } ;
struct TYPE_6__ {int gen; } ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 int I830_FENCE_START_MASK ; 
 int I915_FENCE_START_MASK ; 
 int I915_TILING_NONE ; 
 TYPE_3__* INTEL_INFO (int /*<<< orphan*/ ) ; 
 int i915_gem_get_gtt_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
i915_gem_object_fence_ok(struct drm_i915_gem_object *obj, int tiling_mode)
{
	u32 size;

	if (tiling_mode == I915_TILING_NONE)
		return true;

	if (INTEL_INFO(obj->base.dev)->gen >= 4)
		return true;

	if (INTEL_INFO(obj->base.dev)->gen == 3) {
		if (obj->gtt_offset & ~I915_FENCE_START_MASK)
			return false;
	} else {
		if (obj->gtt_offset & ~I830_FENCE_START_MASK)
			return false;
	}

	size = i915_gem_get_gtt_size(obj->base.dev, obj->base.size, tiling_mode);
	if (obj->gtt_space->size != size)
		return false;

	if (obj->gtt_offset & (size - 1))
		return false;

	return true;
}