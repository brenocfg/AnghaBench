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
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct intel_crtc {int pipe; int /*<<< orphan*/  plane; TYPE_2__ base; } ;
struct drm_i915_private {int num_pipe; } ;
struct TYPE_3__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
 int DISPPLANE_SEL_PIPE_MASK ; 
 int DSPCNTR (int) ; 
 int I915_READ (int) ; 

__attribute__((used)) static bool
intel_check_plane_mapping(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = crtc->base.dev->dev_private;
	u32 reg, val;

	if (dev_priv->num_pipe == 1)
		return true;

	reg = DSPCNTR(!crtc->plane);
	val = I915_READ(reg);

	if ((val & DISPLAY_PLANE_ENABLE) &&
	    (!!(val & DISPPLANE_SEL_PIPE_MASK) == crtc->pipe))
		return false;

	return true;
}