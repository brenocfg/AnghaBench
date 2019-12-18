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
struct TYPE_6__ {int type; int reference_count; } ;
struct TYPE_5__ {size_t length; int /*<<< orphan*/ * pointer; } ;
struct TYPE_4__ {int /*<<< orphan*/  pointer; } ;
union acpi_operand_object {TYPE_3__ common; TYPE_2__ buffer; TYPE_1__ string; } ;
typedef  int u32 ;
struct acpi_predefined_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  node_flags; int /*<<< orphan*/  pathname; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  size_t acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int ACPI_NOT_PACKAGE_ELEMENT ; 
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 int ACPI_RTYPE_STRING ; 
#define  ACPI_TYPE_BUFFER 128 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 union acpi_operand_object* acpi_ut_create_string_object (size_t) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 

acpi_status
acpi_ns_repair_object(struct acpi_predefined_data *data,
		      u32 expected_btypes,
		      u32 package_index,
		      union acpi_operand_object **return_object_ptr)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	union acpi_operand_object *new_object;
	acpi_size length;

	switch (return_object->common.type) {
	case ACPI_TYPE_BUFFER:

		/* Does the method/object legally return a string? */

		if (!(expected_btypes & ACPI_RTYPE_STRING)) {
			return (AE_AML_OPERAND_TYPE);
		}

		/*
		 * Have a Buffer, expected a String, convert. Use a to_string
		 * conversion, no transform performed on the buffer data. The best
		 * example of this is the _BIF method, where the string data from
		 * the battery is often (incorrectly) returned as buffer object(s).
		 */
		length = 0;
		while ((length < return_object->buffer.length) &&
		       (return_object->buffer.pointer[length])) {
			length++;
		}

		/* Allocate a new string object */

		new_object = acpi_ut_create_string_object(length);
		if (!new_object) {
			return (AE_NO_MEMORY);
		}

		/*
		 * Copy the raw buffer data with no transform. String is already NULL
		 * terminated at Length+1.
		 */
		ACPI_MEMCPY(new_object->string.pointer,
			    return_object->buffer.pointer, length);

		/*
		 * If the original object is a package element, we need to:
		 * 1. Set the reference count of the new object to match the
		 *    reference count of the old object.
		 * 2. Decrement the reference count of the original object.
		 */
		if (package_index != ACPI_NOT_PACKAGE_ELEMENT) {
			new_object->common.reference_count =
			    return_object->common.reference_count;

			if (return_object->common.reference_count > 1) {
				return_object->common.reference_count--;
			}

			ACPI_WARN_PREDEFINED((AE_INFO, data->pathname,
					      data->node_flags,
					      "Converted Buffer to expected String at index %u",
					      package_index));
		} else {
			ACPI_WARN_PREDEFINED((AE_INFO, data->pathname,
					      data->node_flags,
					      "Converted Buffer to expected String"));
		}

		/* Delete old object, install the new return object */

		acpi_ut_remove_reference(return_object);
		*return_object_ptr = new_object;
		data->flags |= ACPI_OBJECT_REPAIRED;
		return (AE_OK);

	default:
		break;
	}

	return (AE_AML_OPERAND_TYPE);
}