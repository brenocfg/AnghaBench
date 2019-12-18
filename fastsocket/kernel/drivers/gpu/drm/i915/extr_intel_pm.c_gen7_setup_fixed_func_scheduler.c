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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_i915_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN7_FF_DS_SCHED_HW ; 
 int /*<<< orphan*/  GEN7_FF_SCHED_MASK ; 
 int /*<<< orphan*/  GEN7_FF_THREAD_MODE ; 
 int /*<<< orphan*/  GEN7_FF_TS_SCHED_HW ; 
 int /*<<< orphan*/  GEN7_FF_VS_REF_CNT_FFME ; 
 int /*<<< orphan*/  GEN7_FF_VS_SCHED_HW ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HASWELL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen7_setup_fixed_func_scheduler(struct drm_i915_private *dev_priv)
{
	uint32_t reg = I915_READ(GEN7_FF_THREAD_MODE);

	reg &= ~GEN7_FF_SCHED_MASK;
	reg |= GEN7_FF_TS_SCHED_HW;
	reg |= GEN7_FF_VS_SCHED_HW;
	reg |= GEN7_FF_DS_SCHED_HW;

	/* WaVSRefCountFullforceMissDisable */
	if (IS_HASWELL(dev_priv->dev))
		reg &= ~GEN7_FF_VS_REF_CNT_FFME;

	I915_WRITE(GEN7_FF_THREAD_MODE, reg);
}