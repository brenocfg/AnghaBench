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
typedef  int u32 ;
struct drm_i915_gem_object {int gtt_offset; scalar_t__ tiling_mode; int stride; int /*<<< orphan*/  map_and_fenceable; TYPE_1__* gtt_space; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int FENCE_REG_830_0 ; 
 int FENCE_REG_945_8 ; 
 scalar_t__ HAS_128_BYTE_Y_TILING (struct drm_device*) ; 
 int I830_FENCE_PITCH_SHIFT ; 
 int I830_FENCE_REG_VALID ; 
 int I830_FENCE_TILING_Y_SHIFT ; 
 int I915_FENCE_SIZE_BITS (int) ; 
 int I915_FENCE_START_MASK ; 
 scalar_t__ I915_TILING_Y ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int /*<<< orphan*/  POSTING_READ (int) ; 
 int /*<<< orphan*/  WARN (int,char*,int,int /*<<< orphan*/ ,int) ; 
 int ffs (int) ; 

__attribute__((used)) static void i915_write_fence_reg(struct drm_device *dev, int reg,
				 struct drm_i915_gem_object *obj)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u32 val;

	if (obj) {
		u32 size = obj->gtt_space->size;
		int pitch_val;
		int tile_width;

		WARN((obj->gtt_offset & ~I915_FENCE_START_MASK) ||
		     (size & -size) != size ||
		     (obj->gtt_offset & (size - 1)),
		     "object 0x%08x [fenceable? %d] not 1M or pot-size (0x%08x) aligned\n",
		     obj->gtt_offset, obj->map_and_fenceable, size);

		if (obj->tiling_mode == I915_TILING_Y && HAS_128_BYTE_Y_TILING(dev))
			tile_width = 128;
		else
			tile_width = 512;

		/* Note: pitch better be a power of two tile widths */
		pitch_val = obj->stride / tile_width;
		pitch_val = ffs(pitch_val) - 1;

		val = obj->gtt_offset;
		if (obj->tiling_mode == I915_TILING_Y)
			val |= 1 << I830_FENCE_TILING_Y_SHIFT;
		val |= I915_FENCE_SIZE_BITS(size);
		val |= pitch_val << I830_FENCE_PITCH_SHIFT;
		val |= I830_FENCE_REG_VALID;
	} else
		val = 0;

	if (reg < 8)
		reg = FENCE_REG_830_0 + reg * 4;
	else
		reg = FENCE_REG_945_8 + (reg - 8) * 4;

	I915_WRITE(reg, val);
	POSTING_READ(reg);
}