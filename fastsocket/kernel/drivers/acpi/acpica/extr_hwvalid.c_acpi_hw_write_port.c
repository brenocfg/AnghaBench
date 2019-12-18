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
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_io_address ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_UINT16_MAX ; 
 scalar_t__ AE_AML_ILLEGAL_ADDRESS ; 
 scalar_t__ AE_OK ; 
 scalar_t__ acpi_gbl_truncate_io_addresses ; 
 scalar_t__ acpi_hw_validate_io_request (int /*<<< orphan*/ ,int) ; 
 scalar_t__ acpi_os_write_port (int /*<<< orphan*/ ,int,int) ; 

acpi_status acpi_hw_write_port(acpi_io_address address, u32 value, u32 width)
{
	acpi_status status;
	u32 i;

	/* Truncate address to 16 bits if requested */

	if (acpi_gbl_truncate_io_addresses) {
		address &= ACPI_UINT16_MAX;
	}

	/* Validate the entire request and perform the I/O */

	status = acpi_hw_validate_io_request(address, width);
	if (ACPI_SUCCESS(status)) {
		status = acpi_os_write_port(address, value, width);
		return status;
	}

	if (status != AE_AML_ILLEGAL_ADDRESS) {
		return status;
	}

	/*
	 * There has been a protection violation within the request. Fall
	 * back to byte granularity port I/O and ignore the failing bytes.
	 * This provides Windows compatibility.
	 */
	for (i = 0; i < width; i += 8) {

		/* Validate and write one byte */

		if (acpi_hw_validate_io_request(address, 8) == AE_OK) {
			status =
			    acpi_os_write_port(address, (value >> i) & 0xFF, 8);
			if (ACPI_FAILURE(status)) {
				return status;
			}
		}

		address++;
	}

	return AE_OK;
}