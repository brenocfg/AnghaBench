#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  unbind; int /*<<< orphan*/  bind; } ;
struct acpi_device {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_pci_bind ; 
 int /*<<< orphan*/  acpi_pci_unbind ; 

int acpi_pci_bind_root(struct acpi_device *device)
{
	device->ops.bind = acpi_pci_bind;
	device->ops.unbind = acpi_pci_unbind;

	return 0;
}