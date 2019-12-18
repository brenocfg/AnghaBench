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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  acpi_get_pci_rootbridge_handle (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int acpi_pci_find_root_bridge(struct device *dev, acpi_handle *handle)
{
	int num;
	unsigned int seg, bus;

	/*
	 * The string should be the same as root bridge's name
	 * Please look at 'pci_scan_bus_parented'
	 */
	num = sscanf(dev_name(dev), "pci%04x:%02x", &seg, &bus);
	if (num != 2)
		return -ENODEV;
	*handle = acpi_get_pci_rootbridge_handle(seg, bus);
	if (!*handle)
		return -ENODEV;
	return 0;
}