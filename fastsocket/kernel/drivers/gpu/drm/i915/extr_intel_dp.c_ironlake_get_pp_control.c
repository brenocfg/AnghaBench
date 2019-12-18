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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANEL_UNLOCK_MASK ; 
 int /*<<< orphan*/  PANEL_UNLOCK_REGS ; 
 int /*<<< orphan*/  PCH_PP_CONTROL ; 

__attribute__((used)) static  u32 ironlake_get_pp_control(struct drm_i915_private *dev_priv)
{
	u32	control = I915_READ(PCH_PP_CONTROL);

	control &= ~PANEL_UNLOCK_MASK;
	control |= PANEL_UNLOCK_REGS;
	return control;
}