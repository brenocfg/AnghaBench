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
struct intel_device_info {int /*<<< orphan*/  gen; } ;
struct drm_i915_private {TYPE_2__* dev; struct intel_device_info* info; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_INFO_FLAGS ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_dump_device_info(struct drm_i915_private *dev_priv)
{
	const struct intel_device_info *info = dev_priv->info;

#define DEV_INFO_FLAG(name) info->name ? #name "," : ""
#define DEV_INFO_SEP ,
	DRM_DEBUG_DRIVER("i915 device info: gen=%i, pciid=0x%04x flags="
			 "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
			 info->gen,
			 dev_priv->dev->pdev->device,
			 DEV_INFO_FLAGS);
#undef DEV_INFO_FLAG
#undef DEV_INFO_SEP
}