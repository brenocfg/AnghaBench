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
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_enable_gt_powersave (struct drm_device*) ; 
 int /*<<< orphan*/  intel_init_clock_gating (struct drm_device*) ; 
 int /*<<< orphan*/  intel_init_power_well (struct drm_device*) ; 
 int /*<<< orphan*/  intel_prepare_ddi (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_modeset_init_hw(struct drm_device *dev)
{
	intel_init_power_well(dev);

	intel_prepare_ddi(dev);

	intel_init_clock_gating(dev);

	mutex_lock(&dev->struct_mutex);
	intel_enable_gt_powersave(dev);
	mutex_unlock(&dev->struct_mutex);
}