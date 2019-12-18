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
 int /*<<< orphan*/  ACPI_STRCPY (char*,char*) ; 

__attribute__((used)) static void acpi_ut_copy_id_string(char *destination, char *source)
{

	/*
	 * Workaround for ID strings that have a leading asterisk. This construct
	 * is not allowed by the ACPI specification  (ID strings must be
	 * alphanumeric), but enough existing machines have this embedded in their
	 * ID strings that the following code is useful.
	 */
	if (*source == '*') {
		source++;
	}

	/* Do the actual copy */

	ACPI_STRCPY(destination, source);
}