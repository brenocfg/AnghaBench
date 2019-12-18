#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_1__* primary; } ;
struct TYPE_6__ {int gen; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_2__ kdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ HAS_L3_GPU_CACHE (struct drm_device*) ; 
 TYPE_3__* INTEL_INFO (struct drm_device*) ; 
 int device_create_bin_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpf_attrs ; 
 int /*<<< orphan*/  gen6_attr_group ; 
 int /*<<< orphan*/  rc6_attr_group ; 
 int sysfs_merge_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void i915_setup_sysfs(struct drm_device *dev)
{
	int ret;

#ifdef CONFIG_PM
	if (INTEL_INFO(dev)->gen >= 6) {
		ret = sysfs_merge_group(&dev->primary->kdev.kobj,
					&rc6_attr_group);
		if (ret)
			DRM_ERROR("RC6 residency sysfs setup failed\n");
	}
#endif
	if (HAS_L3_GPU_CACHE(dev)) {
		ret = device_create_bin_file(&dev->primary->kdev, &dpf_attrs);
		if (ret)
			DRM_ERROR("l3 parity sysfs setup failed\n");
	}

	if (INTEL_INFO(dev)->gen >= 6) {
		ret = sysfs_merge_group(&dev->primary->kdev.kobj, &gen6_attr_group);
		if (ret)
			DRM_ERROR("gen6 sysfs setup failed\n");
	}
}