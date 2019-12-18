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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_STRCMP (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PCI_EXPRESS_ROOT_HID_STRING ; 
 int /*<<< orphan*/  PCI_ROOT_HID_STRING ; 
 int /*<<< orphan*/  TRUE ; 

u8 acpi_ut_is_pci_root_bridge(char *id)
{

	/*
	 * Check if this is a PCI root bridge.
	 * ACPI 3.0+: check for a PCI Express root also.
	 */
	if (!(ACPI_STRCMP(id,
			  PCI_ROOT_HID_STRING)) ||
	    !(ACPI_STRCMP(id, PCI_EXPRESS_ROOT_HID_STRING))) {
		return (TRUE);
	}

	return (FALSE);
}