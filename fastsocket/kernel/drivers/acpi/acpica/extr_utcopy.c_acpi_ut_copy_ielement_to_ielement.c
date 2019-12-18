#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  count; } ;
union acpi_operand_object {TYPE_4__ common; TYPE_3__ package; } ;
struct TYPE_10__ {size_t index; union acpi_operand_object* this_target_obj; TYPE_2__* dest_object; } ;
union acpi_generic_state {TYPE_5__ pkg; } ;
typedef  int u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {int /*<<< orphan*/ * elements; } ;
struct TYPE_7__ {TYPE_1__ package; } ;

/* Variables and functions */
#define  ACPI_COPY_TYPE_PACKAGE 129 
#define  ACPI_COPY_TYPE_SIMPLE 128 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ut_copy_simple_object (union acpi_operand_object*,union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ut_create_package_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 

__attribute__((used)) static acpi_status
acpi_ut_copy_ielement_to_ielement(u8 object_type,
				  union acpi_operand_object *source_object,
				  union acpi_generic_state *state,
				  void *context)
{
	acpi_status status = AE_OK;
	u32 this_index;
	union acpi_operand_object **this_target_ptr;
	union acpi_operand_object *target_object;

	ACPI_FUNCTION_ENTRY();

	this_index = state->pkg.index;
	this_target_ptr = (union acpi_operand_object **)
	    &state->pkg.dest_object->package.elements[this_index];

	switch (object_type) {
	case ACPI_COPY_TYPE_SIMPLE:

		/* A null source object indicates a (legal) null package element */

		if (source_object) {
			/*
			 * This is a simple object, just copy it
			 */
			target_object =
			    acpi_ut_create_internal_object(source_object->
							   common.type);
			if (!target_object) {
				return (AE_NO_MEMORY);
			}

			status =
			    acpi_ut_copy_simple_object(source_object,
						       target_object);
			if (ACPI_FAILURE(status)) {
				goto error_exit;
			}

			*this_target_ptr = target_object;
		} else {
			/* Pass through a null element */

			*this_target_ptr = NULL;
		}
		break;

	case ACPI_COPY_TYPE_PACKAGE:

		/*
		 * This object is a package - go down another nesting level
		 * Create and build the package object
		 */
		target_object =
		    acpi_ut_create_package_object(source_object->package.count);
		if (!target_object) {
			return (AE_NO_MEMORY);
		}

		target_object->common.flags = source_object->common.flags;

		/* Pass the new package object back to the package walk routine */

		state->pkg.this_target_obj = target_object;

		/* Store the object pointer in the parent package object */

		*this_target_ptr = target_object;
		break;

	default:
		return (AE_BAD_PARAMETER);
	}

	return (status);

      error_exit:
	acpi_ut_remove_reference(target_object);
	return (status);
}