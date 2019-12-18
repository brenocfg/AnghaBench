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
typedef  union acpi_generic_state {int dummy; } acpi_generic_state ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_state_cache ; 
 int /*<<< orphan*/  acpi_os_release_object (int /*<<< orphan*/ ,union acpi_generic_state*) ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  ut_delete_generic_state ; 

void acpi_ut_delete_generic_state(union acpi_generic_state *state)
{
	ACPI_FUNCTION_TRACE(ut_delete_generic_state);

	/* Ignore null state */

	if (state) {
		(void)acpi_os_release_object(acpi_gbl_state_cache, state);
	}
	return_VOID;
}