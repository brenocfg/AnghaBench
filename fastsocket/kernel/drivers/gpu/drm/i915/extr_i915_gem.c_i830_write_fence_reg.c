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
typedef  int uint32_t ;
typedef  int u32 ;
struct drm_i915_gem_object {int gtt_offset; int stride; scalar_t__ tiling_mode; TYPE_1__* gtt_space; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 scalar_t__ FENCE_REG_830_0 ; 
 int I830_FENCE_PITCH_SHIFT ; 
 int I830_FENCE_REG_VALID ; 
 int I830_FENCE_SIZE_BITS (int) ; 
 int I830_FENCE_START_MASK ; 
 int I830_FENCE_TILING_Y_SHIFT ; 
 scalar_t__ I915_TILING_Y ; 
 int /*<<< orphan*/  I915_WRITE (scalar_t__,int) ; 
 int /*<<< orphan*/  POSTING_READ (scalar_t__) ; 
 int /*<<< orphan*/  WARN (int,char*,int,int) ; 
 int ffs (int) ; 

__attribute__((used)) static void i830_write_fence_reg(struct drm_device *dev, int reg,
				struct drm_i915_gem_object *obj)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	uint32_t val;

	if (obj) {
		u32 size = obj->gtt_space->size;
		uint32_t pitch_val;

		WARN((obj->gtt_offset & ~I830_FENCE_START_MASK) ||
		     (size & -size) != size ||
		     (obj->gtt_offset & (size - 1)),
		     "object 0x%08x not 512K or pot-size 0x%08x aligned\n",
		     obj->gtt_offset, size);

		pitch_val = obj->stride / 128;
		pitch_val = ffs(pitch_val) - 1;

		val = obj->gtt_offset;
		if (obj->tiling_mode == I915_TILING_Y)
			val |= 1 << I830_FENCE_TILING_Y_SHIFT;
		val |= I830_FENCE_SIZE_BITS(size);
		val |= pitch_val << I830_FENCE_PITCH_SHIFT;
		val |= I830_FENCE_REG_VALID;
	} else
		val = 0;

	I915_WRITE(FENCE_REG_830_0 + reg * 4, val);
	POSTING_READ(FENCE_REG_830_0 + reg * 4);
}