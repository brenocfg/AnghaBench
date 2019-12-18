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
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_evaluate_integer (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long*) ; 
 scalar_t__ display_get_handle ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static int read_display(void)
{
	unsigned long long value = 0;
	acpi_status rv = AE_OK;

	/*
	 * In most of the case, we know how to set the display, but sometime
	 * we can't read it
	 */
	if (display_get_handle) {
		rv = acpi_evaluate_integer(display_get_handle, NULL,
					   NULL, &value);
		if (ACPI_FAILURE(rv))
			pr_warning("Error reading display status\n");
	}

	value &= 0x0F;		/* needed for some models, shouldn't hurt others */

	return value;
}