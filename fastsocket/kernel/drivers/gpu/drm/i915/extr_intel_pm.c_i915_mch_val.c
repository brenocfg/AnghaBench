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
typedef  unsigned long u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 unsigned long I915_READ (int /*<<< orphan*/ ) ; 
 unsigned long I915_READ8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TR1 ; 
 int /*<<< orphan*/  TSFS ; 
 unsigned long TSFS_INTR_MASK ; 
 unsigned long TSFS_SLOPE_MASK ; 
 unsigned long TSFS_SLOPE_SHIFT ; 

unsigned long i915_mch_val(struct drm_i915_private *dev_priv)
{
	unsigned long m, x, b;
	u32 tsfs;

	tsfs = I915_READ(TSFS);

	m = ((tsfs & TSFS_SLOPE_MASK) >> TSFS_SLOPE_SHIFT);
	x = I915_READ8(TR1);

	b = tsfs & TSFS_INTR_MASK;

	return ((m * x) / 127) - b;
}