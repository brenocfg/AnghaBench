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
typedef  int u32 ;
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (unsigned long) ; 
 unsigned long PIPEFRAME (int) ; 
 unsigned long PIPEFRAMEPIXEL (int) ; 
 int PIPE_FRAME_HIGH_MASK ; 
 int PIPE_FRAME_HIGH_SHIFT ; 
 int PIPE_FRAME_LOW_MASK ; 
 int PIPE_FRAME_LOW_SHIFT ; 
 int /*<<< orphan*/  i915_pipe_enabled (struct drm_device*,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static u32 i915_get_vblank_counter(struct drm_device *dev, int pipe)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	unsigned long high_frame;
	unsigned long low_frame;
	u32 high1, high2, low;

	if (!i915_pipe_enabled(dev, pipe)) {
		DRM_DEBUG_DRIVER("trying to get vblank count for disabled "
				"pipe %c\n", pipe_name(pipe));
		return 0;
	}

	high_frame = PIPEFRAME(pipe);
	low_frame = PIPEFRAMEPIXEL(pipe);

	/*
	 * High & low register fields aren't synchronized, so make sure
	 * we get a low value that's stable across two reads of the high
	 * register.
	 */
	do {
		high1 = I915_READ(high_frame) & PIPE_FRAME_HIGH_MASK;
		low   = I915_READ(low_frame)  & PIPE_FRAME_LOW_MASK;
		high2 = I915_READ(high_frame) & PIPE_FRAME_HIGH_MASK;
	} while (high1 != high2);

	high1 >>= PIPE_FRAME_HIGH_SHIFT;
	low >>= PIPE_FRAME_LOW_SHIFT;
	return (high1 << 8) | low;
}