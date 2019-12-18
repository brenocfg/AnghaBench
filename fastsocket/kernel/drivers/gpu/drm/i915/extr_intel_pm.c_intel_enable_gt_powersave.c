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
struct TYPE_2__ {int /*<<< orphan*/  delayed_resume_work; } ;
struct drm_i915_private {TYPE_1__ rps; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 scalar_t__ IS_GEN7 (struct drm_device*) ; 
 scalar_t__ IS_IRONLAKE_M (struct drm_device*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  intel_init_emon (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_enable_drps (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_enable_rc6 (struct drm_device*) ; 
 int /*<<< orphan*/  round_jiffies_up_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void intel_enable_gt_powersave(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (IS_IRONLAKE_M(dev)) {
		ironlake_enable_drps(dev);
		ironlake_enable_rc6(dev);
		intel_init_emon(dev);
	} else if ((IS_GEN6(dev) || IS_GEN7(dev)) && !IS_VALLEYVIEW(dev)) {
		/*
		 * PCU communication is slow and this doesn't need to be
		 * done at any specific time, so do this out of our fast path
		 * to make resume and init faster.
		 */
		schedule_delayed_work(&dev_priv->rps.delayed_resume_work,
				      round_jiffies_up_relative(HZ));
	}
}