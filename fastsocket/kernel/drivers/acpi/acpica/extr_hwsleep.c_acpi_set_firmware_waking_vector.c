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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int length; int version; scalar_t__ xfirmware_waking_vector; int /*<<< orphan*/  firmware_waking_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* acpi_gbl_FACS ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_set_firmware_waking_vector(u32 physical_address)
{
	ACPI_FUNCTION_TRACE(acpi_set_firmware_waking_vector);


	/*
	 * According to the ACPI specification 2.0c and later, the 64-bit
	 * waking vector should be cleared and the 32-bit waking vector should
	 * be used, unless we want the wake-up code to be called by the BIOS in
	 * Protected Mode.  Some systems (for example HP dv5-1004nr) are known
	 * to fail to resume if the 64-bit vector is used.
	 */

	/* Set the 32-bit vector */

	acpi_gbl_FACS->firmware_waking_vector = physical_address;

	/* Clear the 64-bit vector if it exists */

	if ((acpi_gbl_FACS->length > 32) && (acpi_gbl_FACS->version >= 1)) {
		acpi_gbl_FACS->xfirmware_waking_vector = 0;
	}

	return_ACPI_STATUS(AE_OK);
}