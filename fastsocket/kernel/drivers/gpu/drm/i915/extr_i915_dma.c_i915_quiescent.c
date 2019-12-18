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
struct drm_device {int /*<<< orphan*/  dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_kernel_lost_context (struct drm_device*) ; 
 int intel_ring_idle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_quiescent(struct drm_device *dev)
{
	i915_kernel_lost_context(dev);
	return intel_ring_idle(LP_RING(dev->dev_private));
}