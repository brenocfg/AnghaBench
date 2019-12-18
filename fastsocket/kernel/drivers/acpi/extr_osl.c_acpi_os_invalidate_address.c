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
typedef  int u8 ;
struct acpi_res_list {int resource_type; int /*<<< orphan*/  end; scalar_t__ start; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;
typedef  scalar_t__ acpi_physical_address ;

/* Variables and functions */
#define  ACPI_ADR_SPACE_CMOS 136 
#define  ACPI_ADR_SPACE_DATA_TABLE 135 
#define  ACPI_ADR_SPACE_EC 134 
#define  ACPI_ADR_SPACE_FIXED_HARDWARE 133 
#define  ACPI_ADR_SPACE_PCI_BAR_TARGET 132 
#define  ACPI_ADR_SPACE_PCI_CONFIG 131 
#define  ACPI_ADR_SPACE_SMBUS 130 
#define  ACPI_ADR_SPACE_SYSTEM_IO 129 
#define  ACPI_ADR_SPACE_SYSTEM_MEMORY 128 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_res_list_del (struct acpi_res_list*) ; 
 int /*<<< orphan*/  acpi_res_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

acpi_status
acpi_os_invalidate_address(
    u8                   space_id,
    acpi_physical_address   address,
    acpi_size               length)
{
	struct acpi_res_list res;

	switch (space_id) {
	case ACPI_ADR_SPACE_SYSTEM_IO:
	case ACPI_ADR_SPACE_SYSTEM_MEMORY:
		/* Only interference checks against SystemIO and SytemMemory
		   are needed */
		res.start = address;
		res.end = address + length - 1;
		res.resource_type = space_id;
		spin_lock(&acpi_res_lock);
		acpi_res_list_del(&res);
		spin_unlock(&acpi_res_lock);
		break;
	case ACPI_ADR_SPACE_PCI_CONFIG:
	case ACPI_ADR_SPACE_EC:
	case ACPI_ADR_SPACE_SMBUS:
	case ACPI_ADR_SPACE_CMOS:
	case ACPI_ADR_SPACE_PCI_BAR_TARGET:
	case ACPI_ADR_SPACE_DATA_TABLE:
	case ACPI_ADR_SPACE_FIXED_HARDWARE:
		break;
	}
	return AE_OK;
}