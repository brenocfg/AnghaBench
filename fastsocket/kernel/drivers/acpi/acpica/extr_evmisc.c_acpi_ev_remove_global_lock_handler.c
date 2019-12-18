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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EVENT_GLOBAL ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  acpi_ev_global_lock_handler ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_present ; 
 int /*<<< orphan*/  acpi_remove_fixed_event_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_remove_global_lock_handler ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status acpi_ev_remove_global_lock_handler(void)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_remove_global_lock_handler);

	acpi_gbl_global_lock_present = FALSE;
	status = acpi_remove_fixed_event_handler(ACPI_EVENT_GLOBAL,
						 acpi_ev_global_lock_handler);

	return_ACPI_STATUS(status);
}