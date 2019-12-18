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
struct TYPE_3__ {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  delayed_resume_work; } ;
struct drm_i915_private {TYPE_1__ rps; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_IRONLAKE_M (struct drm_device*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen6_disable_rps (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_disable_drps (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_disable_rc6 (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_disable_gt_powersave(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (IS_IRONLAKE_M(dev)) {
		ironlake_disable_drps(dev);
		ironlake_disable_rc6(dev);
	} else if (INTEL_INFO(dev)->gen >= 6 && !IS_VALLEYVIEW(dev)) {
		cancel_delayed_work_sync(&dev_priv->rps.delayed_resume_work);
		mutex_lock(&dev_priv->rps.hw_lock);
		gen6_disable_rps(dev);
		mutex_unlock(&dev_priv->rps.hw_lock);
	}
}