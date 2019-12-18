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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int acpi_pci_detect_ejectable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_pci_dock_device ; 

__attribute__((used)) static int detect_ejectable_slots(acpi_handle handle)
{
	int found = acpi_pci_detect_ejectable(handle);
	if (!found) {
		acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, (u32)1,
				    is_pci_dock_device, (void *)&found, NULL);
	}
	return found;
}