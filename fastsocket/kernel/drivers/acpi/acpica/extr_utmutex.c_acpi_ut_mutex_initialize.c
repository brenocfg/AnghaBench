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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_NUM_MUTEX ; 
 int /*<<< orphan*/  acpi_ev_global_lock_pending_lock ; 
 int /*<<< orphan*/  acpi_gbl_gpe_lock ; 
 int /*<<< orphan*/  acpi_gbl_hardware_lock ; 
 int /*<<< orphan*/  acpi_gbl_namespace_rw_lock ; 
 int /*<<< orphan*/  acpi_ut_create_mutex (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_create_rw_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_mutex_initialize ; 

acpi_status acpi_ut_mutex_initialize(void)
{
	u32 i;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_mutex_initialize);

	/* Create each of the predefined mutex objects */

	for (i = 0; i < ACPI_NUM_MUTEX; i++) {
		status = acpi_ut_create_mutex(i);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
	}

	/* Create the spinlocks for use at interrupt level */

	spin_lock_init(acpi_gbl_gpe_lock);
	spin_lock_init(acpi_gbl_hardware_lock);
	spin_lock_init(acpi_ev_global_lock_pending_lock);

	/* Create the reader/writer lock for namespace access */

	status = acpi_ut_create_rw_lock(&acpi_gbl_namespace_rw_lock);
	return_ACPI_STATUS(status);
}