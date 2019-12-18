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
struct acpi_generic_address {scalar_t__ space_id; scalar_t__ address; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_io_address ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  reset_value; struct acpi_generic_address reset_register; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_IO ; 
 int ACPI_FADT_RESET_REGISTER ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_hw_write (int /*<<< orphan*/ ,struct acpi_generic_address*) ; 
 int /*<<< orphan*/  acpi_os_write_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_reset(void)
{
	struct acpi_generic_address *reset_reg;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_reset);

	reset_reg = &acpi_gbl_FADT.reset_register;

	/* Check if the reset register is supported */

	if (!(acpi_gbl_FADT.flags & ACPI_FADT_RESET_REGISTER) ||
	    !reset_reg->address) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	if (reset_reg->space_id == ACPI_ADR_SPACE_SYSTEM_IO) {
		/*
		 * For I/O space, write directly to the OSL. This
		 * bypasses the port validation mechanism, which may
		 * block a valid write to the reset register. Spec
		 * section 4.7.3.6 requires register width to be 8.
		 */
		status =
		    acpi_os_write_port((acpi_io_address) reset_reg->address,
				       acpi_gbl_FADT.reset_value, 8);
	} else {
		/* Write the reset value to the reset register */

		status = acpi_hw_write(acpi_gbl_FADT.reset_value, reset_reg);
	}

	return_ACPI_STATUS(status);
}