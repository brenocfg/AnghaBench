#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
struct TYPE_2__ {int /*<<< orphan*/ * this_target_obj; } ;
union acpi_generic_state {TYPE_1__ pkg; } ;
typedef  int u8 ;
struct acpi_pkg_info {int /*<<< orphan*/  num_packages; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
#define  ACPI_COPY_TYPE_PACKAGE 129 
#define  ACPI_COPY_TYPE_SIMPLE 128 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ut_get_simple_object_size (union acpi_operand_object*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
acpi_ut_get_element_length(u8 object_type,
			   union acpi_operand_object *source_object,
			   union acpi_generic_state *state, void *context)
{
	acpi_status status = AE_OK;
	struct acpi_pkg_info *info = (struct acpi_pkg_info *)context;
	acpi_size object_space;

	switch (object_type) {
	case ACPI_COPY_TYPE_SIMPLE:

		/*
		 * Simple object - just get the size (Null object/entry is handled
		 * here also) and sum it into the running package length
		 */
		status =
		    acpi_ut_get_simple_object_size(source_object,
						   &object_space);
		if (ACPI_FAILURE(status)) {
			return (status);
		}

		info->length += object_space;
		break;

	case ACPI_COPY_TYPE_PACKAGE:

		/* Package object - nothing much to do here, let the walk handle it */

		info->num_packages++;
		state->pkg.this_target_obj = NULL;
		break;

	default:

		/* No other types allowed */

		return (AE_BAD_PARAMETER);
	}

	return (status);
}