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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_NUM_MUTEX ; 
 int /*<<< orphan*/  acpi_gbl_gpe_lock ; 
 int /*<<< orphan*/  acpi_gbl_hardware_lock ; 
 int /*<<< orphan*/  acpi_gbl_namespace_rw_lock ; 
 int /*<<< orphan*/  acpi_os_delete_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_delete_mutex (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_delete_rw_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  ut_mutex_terminate ; 

void acpi_ut_mutex_terminate(void)
{
	u32 i;

	ACPI_FUNCTION_TRACE(ut_mutex_terminate);

	/* Delete each predefined mutex object */

	for (i = 0; i < ACPI_NUM_MUTEX; i++) {
		(void)acpi_ut_delete_mutex(i);
	}

	/* Delete the spinlocks */

	acpi_os_delete_lock(acpi_gbl_gpe_lock);
	acpi_os_delete_lock(acpi_gbl_hardware_lock);

	/* Delete the reader/writer lock */

	acpi_ut_delete_rw_lock(&acpi_gbl_namespace_rw_lock);
	return_VOID;
}