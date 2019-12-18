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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 union acpi_generic_state* acpi_ut_create_pkg_state (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_push_generic_state (union acpi_generic_state**,union acpi_generic_state*) ; 

acpi_status
acpi_ut_create_pkg_state_and_push(void *internal_object,
				  void *external_object,
				  u16 index,
				  union acpi_generic_state **state_list)
{
	union acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	state =
	    acpi_ut_create_pkg_state(internal_object, external_object, index);
	if (!state) {
		return (AE_NO_MEMORY);
	}

	acpi_ut_push_generic_state(state_list, state);
	return (AE_OK);
}