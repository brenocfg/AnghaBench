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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
typedef  int /*<<< orphan*/  acpi_io_address ;
typedef  int acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_NATIVE_UINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
#define  ACPI_READ 129 
#define  ACPI_WRITE 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_hw_read_port (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  acpi_hw_write_port (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ex_system_io_space_handler ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_system_io_space_handler(u32 function,
				acpi_physical_address address,
				u32 bit_width,
				acpi_integer * value,
				void *handler_context, void *region_context)
{
	acpi_status status = AE_OK;
	u32 value32;

	ACPI_FUNCTION_TRACE(ex_system_io_space_handler);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "System-IO (width %d) R/W %d Address=%8.8X%8.8X\n",
			  bit_width, function,
			  ACPI_FORMAT_NATIVE_UINT(address)));

	/* Decode the function parameter */

	switch (function) {
	case ACPI_READ:

		status = acpi_hw_read_port((acpi_io_address) address,
					   &value32, bit_width);
		*value = value32;
		break;

	case ACPI_WRITE:

		status = acpi_hw_write_port((acpi_io_address) address,
					    (u32) * value, bit_width);
		break;

	default:
		status = AE_BAD_PARAMETER;
		break;
	}

	return_ACPI_STATUS(status);
}