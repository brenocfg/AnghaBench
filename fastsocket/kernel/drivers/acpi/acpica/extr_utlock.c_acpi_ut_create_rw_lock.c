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
struct acpi_rw_lock {int /*<<< orphan*/  writer_mutex; int /*<<< orphan*/  reader_mutex; scalar_t__ num_readers; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_create_mutex (int /*<<< orphan*/ *) ; 

acpi_status acpi_ut_create_rw_lock(struct acpi_rw_lock *lock)
{
	acpi_status status;

	lock->num_readers = 0;
	status = acpi_os_create_mutex(&lock->reader_mutex);
	if (ACPI_FAILURE(status)) {
		return status;
	}

	status = acpi_os_create_mutex(&lock->writer_mutex);
	return status;
}