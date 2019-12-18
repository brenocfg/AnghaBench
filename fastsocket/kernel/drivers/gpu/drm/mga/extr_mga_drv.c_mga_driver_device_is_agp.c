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
struct pci_dev {int device; TYPE_2__* bus; } ;
struct drm_device {struct pci_dev* pdev; } ;
struct TYPE_4__ {TYPE_1__* self; } ;
struct TYPE_3__ {int vendor; int device; } ;

/* Variables and functions */

__attribute__((used)) static int mga_driver_device_is_agp(struct drm_device *dev)
{
	const struct pci_dev *const pdev = dev->pdev;

	/* There are PCI versions of the G450.  These cards have the
	 * same PCI ID as the AGP G450, but have an additional PCI-to-PCI
	 * bridge chip.  We detect these cards, which are not currently
	 * supported by this driver, by looking at the device ID of the
	 * bus the "card" is on.  If vendor is 0x3388 (Hint Corp) and the
	 * device is 0x0021 (HB6 Universal PCI-PCI bridge), we reject the
	 * device.
	 */

	if ((pdev->device == 0x0525) && pdev->bus->self
	    && (pdev->bus->self->vendor == 0x3388)
	    && (pdev->bus->self->device == 0x0021)) {
		return 0;
	}

	return 2;
}