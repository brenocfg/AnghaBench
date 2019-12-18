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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_ejectable(acpi_handle handle)
{
	acpi_status status;
	acpi_handle tmp;
	unsigned long long removable;
	status = acpi_get_handle(handle, "_ADR", &tmp);
	if (ACPI_FAILURE(status))
		return 0;
	status = acpi_get_handle(handle, "_EJ0", &tmp);
	if (ACPI_SUCCESS(status))
		return 1;
	status = acpi_evaluate_integer(handle, "_RMV", NULL, &removable);
	if (ACPI_SUCCESS(status) && removable)
		return 1;
	return 0;
}