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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;
struct TYPE_2__ {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITMASK_ALL_FIXED_STATUS ; 
 int /*<<< orphan*/  ACPI_DB_IO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REGISTER_PM1_STATUS ; 
 int /*<<< orphan*/  acpi_ev_walk_gpe_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_gbl_hardware_lock ; 
 TYPE_1__ acpi_gbl_xpm1a_status ; 
 int /*<<< orphan*/  acpi_hw_clear_gpe_block ; 
 int /*<<< orphan*/  acpi_hw_register_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_acquire_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_clear_acpi_status ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_hw_clear_acpi_status(void)
{
	acpi_status status;
	acpi_cpu_flags lock_flags = 0;

	ACPI_FUNCTION_TRACE(hw_clear_acpi_status);

	ACPI_DEBUG_PRINT((ACPI_DB_IO, "About to write %04X to %8.8X%8.8X\n",
			  ACPI_BITMASK_ALL_FIXED_STATUS,
			  ACPI_FORMAT_UINT64(acpi_gbl_xpm1a_status.address)));

	lock_flags = acpi_os_acquire_lock(acpi_gbl_hardware_lock);

	/* Clear the fixed events in PM1 A/B */

	status = acpi_hw_register_write(ACPI_REGISTER_PM1_STATUS,
					ACPI_BITMASK_ALL_FIXED_STATUS);
	if (ACPI_FAILURE(status)) {
		goto unlock_and_exit;
	}

	/* Clear the GPE Bits in all GPE registers in all GPE blocks */

	status = acpi_ev_walk_gpe_list(acpi_hw_clear_gpe_block, NULL);

      unlock_and_exit:
	acpi_os_release_lock(acpi_gbl_hardware_lock, lock_flags);
	return_ACPI_STATUS(status);
}