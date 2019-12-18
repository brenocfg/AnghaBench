#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int dummy; } ;
struct drm_device {TYPE_1__* pdev; void* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long RADEON_IS_AGP ; 
 unsigned long RADEON_IS_PCI ; 
 unsigned long RADEON_IS_PCIE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ drm_pci_device_is_agp (struct drm_device*) ; 
 struct radeon_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_pcie (TYPE_1__*) ; 
 int radeon_acpi_init (struct radeon_device*) ; 
 int radeon_device_init (struct radeon_device*,struct drm_device*,TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  radeon_driver_unload_kms (struct drm_device*) ; 
 int radeon_modeset_init (struct radeon_device*) ; 

int radeon_driver_load_kms(struct drm_device *dev, unsigned long flags)
{
	struct radeon_device *rdev;
	int r, acpi_status;

	rdev = kzalloc(sizeof(struct radeon_device), GFP_KERNEL);
	if (rdev == NULL) {
		return -ENOMEM;
	}
	dev->dev_private = (void *)rdev;

	/* update BUS flag */
	if (drm_pci_device_is_agp(dev)) {
		flags |= RADEON_IS_AGP;
	} else if (pci_is_pcie(dev->pdev)) {
		flags |= RADEON_IS_PCIE;
	} else {
		flags |= RADEON_IS_PCI;
	}

	/* radeon_device_init should report only fatal error
	 * like memory allocation failure or iomapping failure,
	 * or memory manager initialization failure, it must
	 * properly initialize the GPU MC controller and permit
	 * VRAM allocation
	 */
	r = radeon_device_init(rdev, dev, dev->pdev, flags);
	if (r) {
		dev_err(&dev->pdev->dev, "Fatal error during GPU init\n");
		goto out;
	}

	/* Again modeset_init should fail only on fatal error
	 * otherwise it should provide enough functionalities
	 * for shadowfb to run
	 */
	r = radeon_modeset_init(rdev);
	if (r)
		dev_err(&dev->pdev->dev, "Fatal error during modeset init\n");

	/* Call ACPI methods: require modeset init
	 * but failure is not fatal
	 */
	if (!r) {
		acpi_status = radeon_acpi_init(rdev);
		if (acpi_status)
		dev_dbg(&dev->pdev->dev,
				"Error during ACPI methods call\n");
	}

out:
	if (r)
		radeon_driver_unload_kms(dev);
	return r;
}