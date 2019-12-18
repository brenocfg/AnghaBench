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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ev_terminate () ; 
 int /*<<< orphan*/  acpi_ns_terminate () ; 
 int /*<<< orphan*/  acpi_tb_terminate () ; 
 int /*<<< orphan*/  acpi_ut_delete_caches () ; 
 int /*<<< orphan*/  acpi_ut_terminate () ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  ut_subsystem_shutdown ; 

void acpi_ut_subsystem_shutdown(void)
{
	ACPI_FUNCTION_TRACE(ut_subsystem_shutdown);

#ifndef ACPI_ASL_COMPILER

	/* Close the acpi_event Handling */

	acpi_ev_terminate();
#endif

	/* Close the Namespace */

	acpi_ns_terminate();

	/* Delete the ACPI tables */

	acpi_tb_terminate();

	/* Close the globals */

	acpi_ut_terminate();

	/* Purge the local caches */

	(void)acpi_ut_delete_caches();
	return_VOID;
}