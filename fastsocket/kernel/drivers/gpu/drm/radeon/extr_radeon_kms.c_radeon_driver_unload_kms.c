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
struct radeon_device {int /*<<< orphan*/ * rmmio; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_acpi_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_device_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_modeset_fini (struct radeon_device*) ; 

int radeon_driver_unload_kms(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;

	if (rdev == NULL)
		return 0;
	if (rdev->rmmio == NULL)
		goto done_free;
	radeon_acpi_fini(rdev);
	radeon_modeset_fini(rdev);
	radeon_device_fini(rdev);

done_free:
	kfree(rdev);
	dev->dev_private = NULL;
	return 0;
}