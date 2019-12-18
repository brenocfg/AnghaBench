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
struct acpi_pci_id {int /*<<< orphan*/  bus; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_os_derive_pci_id_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_pci_id**,int*,int /*<<< orphan*/ *) ; 

void acpi_os_derive_pci_id(acpi_handle rhandle,	/* upper bound  */
			   acpi_handle chandle,	/* current node */
			   struct acpi_pci_id **id)
{
	int is_bridge = 1;
	u8 bus_number = (*id)->bus;

	acpi_os_derive_pci_id_2(rhandle, chandle, id, &is_bridge, &bus_number);
}