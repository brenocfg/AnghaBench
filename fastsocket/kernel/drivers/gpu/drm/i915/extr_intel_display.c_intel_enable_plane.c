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
struct drm_i915_private {int /*<<< orphan*/  dev; } ;
typedef  enum plane { ____Placeholder_plane } plane ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
 int DSPCNTR (int) ; 
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int /*<<< orphan*/  assert_pipe_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_flush_display_plane (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intel_enable_plane(struct drm_i915_private *dev_priv,
			       enum plane plane, enum pipe pipe)
{
	int reg;
	u32 val;

	/* If the pipe isn't enabled, we can't pump pixels and may hang */
	assert_pipe_enabled(dev_priv, pipe);

	reg = DSPCNTR(plane);
	val = I915_READ(reg);
	if (val & DISPLAY_PLANE_ENABLE)
		return;

	I915_WRITE(reg, val | DISPLAY_PLANE_ENABLE);
	intel_flush_display_plane(dev_priv, plane);
	intel_wait_for_vblank(dev_priv->dev, pipe);
}