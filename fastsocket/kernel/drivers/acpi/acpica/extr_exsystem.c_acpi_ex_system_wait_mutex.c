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
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_mutex ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DO_NOT_WAIT ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ AE_TIME ; 
 int /*<<< orphan*/  acpi_ex_reacquire_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_relinquish_interpreter () ; 
 int /*<<< orphan*/  acpi_format_exception (scalar_t__) ; 
 scalar_t__ acpi_os_acquire_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_system_wait_mutex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status acpi_ex_system_wait_mutex(acpi_mutex mutex, u16 timeout)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_system_wait_mutex);

	status = acpi_os_acquire_mutex(mutex, ACPI_DO_NOT_WAIT);
	if (ACPI_SUCCESS(status)) {
		return_ACPI_STATUS(status);
	}

	if (status == AE_TIME) {

		/* We must wait, so unlock the interpreter */

		acpi_ex_relinquish_interpreter();

		status = acpi_os_acquire_mutex(mutex, timeout);

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "*** Thread awake after blocking, %s\n",
				  acpi_format_exception(status)));

		/* Reacquire the interpreter */

		acpi_ex_reacquire_interpreter();
	}

	return_ACPI_STATUS(status);
}