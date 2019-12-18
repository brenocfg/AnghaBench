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

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int GEN6_GT_THREAD_STATUS_CORE_MASK ; 
 int GEN6_GT_THREAD_STATUS_CORE_MASK_HSW ; 
 int /*<<< orphan*/  GEN6_GT_THREAD_STATUS_REG ; 
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HASWELL (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_atomic_us (int,int) ; 

__attribute__((used)) static void __gen6_gt_wait_for_thread_c0(struct drm_i915_private *dev_priv)
{
	u32 gt_thread_status_mask;

	if (IS_HASWELL(dev_priv->dev))
		gt_thread_status_mask = GEN6_GT_THREAD_STATUS_CORE_MASK_HSW;
	else
		gt_thread_status_mask = GEN6_GT_THREAD_STATUS_CORE_MASK;

	/* w/a for a sporadic read returning 0 by waiting for the GT
	 * thread to wake up.
	 */
	if (wait_for_atomic_us((I915_READ_NOTRACE(GEN6_GT_THREAD_STATUS_REG) & gt_thread_status_mask) == 0, 500))
		DRM_ERROR("GT thread status wait timed out\n");
}