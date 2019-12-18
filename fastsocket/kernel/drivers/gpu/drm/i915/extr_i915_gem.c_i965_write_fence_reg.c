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
typedef  int uint64_t ;
typedef  int u32 ;
struct drm_i915_gem_object {int gtt_offset; int stride; scalar_t__ tiling_mode; TYPE_1__* gtt_space; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_4__ {int gen; } ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int FENCE_REG_965_0 ; 
 int FENCE_REG_SANDYBRIDGE_0 ; 
 scalar_t__ I915_TILING_Y ; 
 int /*<<< orphan*/  I915_WRITE64 (int,int) ; 
 int I965_FENCE_PITCH_SHIFT ; 
 int I965_FENCE_REG_VALID ; 
 int I965_FENCE_TILING_Y_SHIFT ; 
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  POSTING_READ (int) ; 
 int SANDYBRIDGE_FENCE_PITCH_SHIFT ; 

__attribute__((used)) static void i965_write_fence_reg(struct drm_device *dev, int reg,
				 struct drm_i915_gem_object *obj)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int fence_reg;
	int fence_pitch_shift;
	uint64_t val;

	if (INTEL_INFO(dev)->gen >= 6) {
		fence_reg = FENCE_REG_SANDYBRIDGE_0;
		fence_pitch_shift = SANDYBRIDGE_FENCE_PITCH_SHIFT;
	} else {
		fence_reg = FENCE_REG_965_0;
		fence_pitch_shift = I965_FENCE_PITCH_SHIFT;
	}

	if (obj) {
		u32 size = obj->gtt_space->size;

		val = (uint64_t)((obj->gtt_offset + size - 4096) &
				 0xfffff000) << 32;
		val |= obj->gtt_offset & 0xfffff000;
		val |= (uint64_t)((obj->stride / 128) - 1) << fence_pitch_shift;
		if (obj->tiling_mode == I915_TILING_Y)
			val |= 1 << I965_FENCE_TILING_Y_SHIFT;
		val |= I965_FENCE_REG_VALID;
	} else
		val = 0;

	fence_reg += reg * 8;
	I915_WRITE64(fence_reg, val);
	POSTING_READ(fence_reg);
}