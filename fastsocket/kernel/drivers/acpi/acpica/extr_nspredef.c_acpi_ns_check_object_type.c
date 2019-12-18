#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
struct TYPE_4__ {int /*<<< orphan*/  ascii; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; TYPE_1__ name; } ;
union acpi_operand_object {TYPE_3__ common; TYPE_2__ node; } ;
typedef  scalar_t__ u32 ;
struct acpi_predefined_data {int /*<<< orphan*/  node_flags; int /*<<< orphan*/  pathname; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 scalar_t__ ACPI_NOT_PACKAGE_ELEMENT ; 
 scalar_t__ ACPI_RTYPE_BUFFER ; 
 scalar_t__ ACPI_RTYPE_INTEGER ; 
 scalar_t__ ACPI_RTYPE_PACKAGE ; 
 scalar_t__ ACPI_RTYPE_REFERENCE ; 
 scalar_t__ ACPI_RTYPE_STRING ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER 132 
#define  ACPI_TYPE_INTEGER 131 
#define  ACPI_TYPE_LOCAL_REFERENCE 130 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_check_reference (struct acpi_predefined_data*,union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ns_get_expected_types (char*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_ns_repair_object (struct acpi_predefined_data*,scalar_t__,scalar_t__,union acpi_operand_object**) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ns_check_object_type(struct acpi_predefined_data *data,
			  union acpi_operand_object **return_object_ptr,
			  u32 expected_btypes, u32 package_index)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	acpi_status status = AE_OK;
	u32 return_btype;
	char type_buffer[48];	/* Room for 5 types */

	/*
	 * If we get a NULL return_object here, it is a NULL package element,
	 * and this is always an error.
	 */
	if (!return_object) {
		goto type_error_exit;
	}

	/* A Namespace node should not get here, but make sure */

	if (ACPI_GET_DESCRIPTOR_TYPE(return_object) == ACPI_DESC_TYPE_NAMED) {
		ACPI_WARN_PREDEFINED((AE_INFO, data->pathname, data->node_flags,
				      "Invalid return type - Found a Namespace node [%4.4s] type %s",
				      return_object->node.name.ascii,
				      acpi_ut_get_type_name(return_object->node.
							    type)));
		return (AE_AML_OPERAND_TYPE);
	}

	/*
	 * Convert the object type (ACPI_TYPE_xxx) to a bitmapped object type.
	 * The bitmapped type allows multiple possible return types.
	 *
	 * Note, the cases below must handle all of the possible types returned
	 * from all of the predefined names (including elements of returned
	 * packages)
	 */
	switch (return_object->common.type) {
	case ACPI_TYPE_INTEGER:
		return_btype = ACPI_RTYPE_INTEGER;
		break;

	case ACPI_TYPE_BUFFER:
		return_btype = ACPI_RTYPE_BUFFER;
		break;

	case ACPI_TYPE_STRING:
		return_btype = ACPI_RTYPE_STRING;
		break;

	case ACPI_TYPE_PACKAGE:
		return_btype = ACPI_RTYPE_PACKAGE;
		break;

	case ACPI_TYPE_LOCAL_REFERENCE:
		return_btype = ACPI_RTYPE_REFERENCE;
		break;

	default:
		/* Not one of the supported objects, must be incorrect */

		goto type_error_exit;
	}

	/* Is the object one of the expected types? */

	if (!(return_btype & expected_btypes)) {

		/* Type mismatch -- attempt repair of the returned object */

		status = acpi_ns_repair_object(data, expected_btypes,
					       package_index,
					       return_object_ptr);
		if (ACPI_SUCCESS(status)) {
			return (AE_OK);	/* Repair was successful */
		}
		goto type_error_exit;
	}

	/* For reference objects, check that the reference type is correct */

	if (return_object->common.type == ACPI_TYPE_LOCAL_REFERENCE) {
		status = acpi_ns_check_reference(data, return_object);
	}

	return (status);

      type_error_exit:

	/* Create a string with all expected types for this predefined object */

	acpi_ns_get_expected_types(type_buffer, expected_btypes);

	if (package_index == ACPI_NOT_PACKAGE_ELEMENT) {
		ACPI_WARN_PREDEFINED((AE_INFO, data->pathname, data->node_flags,
				      "Return type mismatch - found %s, expected %s",
				      acpi_ut_get_object_type_name
				      (return_object), type_buffer));
	} else {
		ACPI_WARN_PREDEFINED((AE_INFO, data->pathname, data->node_flags,
				      "Return Package type mismatch at index %u - "
				      "found %s, expected %s", package_index,
				      acpi_ut_get_object_type_name
				      (return_object), type_buffer));
	}

	return (AE_AML_OPERAND_TYPE);
}