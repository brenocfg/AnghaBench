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
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ DEVICE_ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int acpi_bus_power_manageable (scalar_t__) ; 

__attribute__((used)) static bool acpi_pci_power_manageable(struct pci_dev *dev)
{
	acpi_handle handle = DEVICE_ACPI_HANDLE(&dev->dev);

	return handle ? acpi_bus_power_manageable(handle) : false;
}