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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct acpi_generic_address {scalar_t__ space_id; int /*<<< orphan*/  bit_width; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
typedef  int /*<<< orphan*/  acpi_io_address ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  ACPI_DB_IO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_hw_validate_register (struct acpi_generic_address*,int,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_hw_write_port (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_write_memory (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (scalar_t__) ; 
 int /*<<< orphan*/  hw_write ; 

acpi_status acpi_hw_write(u32 value, struct acpi_generic_address *reg)
{
	u64 address;
	acpi_status status;

	ACPI_FUNCTION_NAME(hw_write);

	/* Validate contents of the GAS register */

	status = acpi_hw_validate_register(reg, 32, &address);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/*
	 * Two address spaces supported: Memory or IO. PCI_Config is
	 * not supported here because the GAS structure is insufficient
	 */
	if (reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) {
		status = acpi_os_write_memory((acpi_physical_address)
					      address, (u64)value,
					      reg->bit_width);
	} else {		/* ACPI_ADR_SPACE_SYSTEM_IO, validated earlier */

		status = acpi_hw_write_port((acpi_io_address)
					    address, value, reg->bit_width);
	}

	ACPI_DEBUG_PRINT((ACPI_DB_IO,
			  "Wrote: %8.8X width %2d   to %8.8X%8.8X (%s)\n",
			  value, reg->bit_width, ACPI_FORMAT_UINT64(address),
			  acpi_ut_get_region_name(reg->space_id)));

	return (status);
}