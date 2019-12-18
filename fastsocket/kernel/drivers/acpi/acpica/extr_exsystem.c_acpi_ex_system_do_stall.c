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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_os_stall (int) ; 

acpi_status acpi_ex_system_do_stall(u32 how_long)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_ENTRY();

	if (how_long > 255) {	/* 255 microseconds */
		/*
		 * Longer than 255 usec, this is an error
		 *
		 * (ACPI specifies 100 usec as max, but this gives some slack in
		 * order to support existing BIOSs)
		 */
		ACPI_ERROR((AE_INFO, "Time parameter is too large (%d)",
			    how_long));
		status = AE_AML_OPERAND_VALUE;
	} else {
		acpi_os_stall(how_long);
	}

	return (status);
}