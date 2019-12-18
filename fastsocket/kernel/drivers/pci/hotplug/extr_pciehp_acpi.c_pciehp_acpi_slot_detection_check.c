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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 scalar_t__ PCIEHP_DETECT_ACPI ; 
 scalar_t__ acpi_pci_detect_ejectable (int /*<<< orphan*/ ) ; 
 scalar_t__ slot_detection_mode ; 

int pciehp_acpi_slot_detection_check(struct pci_dev *dev)
{
	if (slot_detection_mode != PCIEHP_DETECT_ACPI)
		return 0;
	if (acpi_pci_detect_ejectable(DEVICE_ACPI_HANDLE(&dev->dev)))
		return 0;
	return -ENODEV;
}