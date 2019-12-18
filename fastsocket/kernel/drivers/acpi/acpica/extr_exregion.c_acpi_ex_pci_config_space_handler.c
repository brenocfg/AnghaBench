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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct acpi_pci_id {int /*<<< orphan*/  function; int /*<<< orphan*/  device; int /*<<< orphan*/  bus; int /*<<< orphan*/  segment; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_physical_address ;
typedef  int acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
#define  ACPI_READ 129 
#define  ACPI_WRITE 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_os_read_pci_configuration (struct acpi_pci_id*,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  acpi_os_write_pci_configuration (struct acpi_pci_id*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ex_pci_config_space_handler ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_pci_config_space_handler(u32 function,
				 acpi_physical_address address,
				 u32 bit_width,
				 acpi_integer * value,
				 void *handler_context, void *region_context)
{
	acpi_status status = AE_OK;
	struct acpi_pci_id *pci_id;
	u16 pci_register;
	u32 value32;

	ACPI_FUNCTION_TRACE(ex_pci_config_space_handler);

	/*
	 *  The arguments to acpi_os(Read|Write)pci_configuration are:
	 *
	 *  pci_segment is the PCI bus segment range 0-31
	 *  pci_bus     is the PCI bus number range 0-255
	 *  pci_device  is the PCI device number range 0-31
	 *  pci_function is the PCI device function number
	 *  pci_register is the Config space register range 0-255 bytes
	 *
	 *  Value - input value for write, output address for read
	 *
	 */
	pci_id = (struct acpi_pci_id *)region_context;
	pci_register = (u16) (u32) address;

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Pci-Config %d (%d) Seg(%04x) Bus(%04x) Dev(%04x) Func(%04x) Reg(%04x)\n",
			  function, bit_width, pci_id->segment, pci_id->bus,
			  pci_id->device, pci_id->function, pci_register));

	switch (function) {
	case ACPI_READ:

		status = acpi_os_read_pci_configuration(pci_id, pci_register,
							&value32, bit_width);
		*value = value32;
		break;

	case ACPI_WRITE:

		status = acpi_os_write_pci_configuration(pci_id, pci_register,
							 *value, bit_width);
		break;

	default:

		status = AE_BAD_PARAMETER;
		break;
	}

	return_ACPI_STATUS(status);
}