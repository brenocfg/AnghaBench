#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int target_type; size_t value; union acpi_operand_object* object; union acpi_operand_object** where; int /*<<< orphan*/  class; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pointer; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int type; int reference_count; } ;
union acpi_operand_object {TYPE_4__ reference; TYPE_3__ buffer; TYPE_2__ integer; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REFCLASS_TABLE ; 
#define  ACPI_TYPE_BUFFER 132 
#define  ACPI_TYPE_BUFFER_FIELD 131 
#define  ACPI_TYPE_INTEGER 130 
 int ACPI_TYPE_LOCAL_REFERENCE ; 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ut_add_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_copy_iobject_to_iobject (union acpi_operand_object*,union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_store_object_to_index ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ex_store_object_to_index(union acpi_operand_object *source_desc,
			      union acpi_operand_object *index_desc,
			      struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *obj_desc;
	union acpi_operand_object *new_desc;
	u8 value = 0;
	u32 i;

	ACPI_FUNCTION_TRACE(ex_store_object_to_index);

	/*
	 * Destination must be a reference pointer, and
	 * must point to either a buffer or a package
	 */
	switch (index_desc->reference.target_type) {
	case ACPI_TYPE_PACKAGE:
		/*
		 * Storing to a package element. Copy the object and replace
		 * any existing object with the new object. No implicit
		 * conversion is performed.
		 *
		 * The object at *(index_desc->Reference.Where) is the
		 * element within the package that is to be modified.
		 * The parent package object is at index_desc->Reference.Object
		 */
		obj_desc = *(index_desc->reference.where);

		if (source_desc->common.type == ACPI_TYPE_LOCAL_REFERENCE &&
		    source_desc->reference.class == ACPI_REFCLASS_TABLE) {

			/* This is a DDBHandle, just add a reference to it */

			acpi_ut_add_reference(source_desc);
			new_desc = source_desc;
		} else {
			/* Normal object, copy it */

			status =
			    acpi_ut_copy_iobject_to_iobject(source_desc,
							    &new_desc,
							    walk_state);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}
		}

		if (obj_desc) {

			/* Decrement reference count by the ref count of the parent package */

			for (i = 0; i < ((union acpi_operand_object *)
					 index_desc->reference.object)->common.
			     reference_count; i++) {
				acpi_ut_remove_reference(obj_desc);
			}
		}

		*(index_desc->reference.where) = new_desc;

		/* Increment ref count by the ref count of the parent package-1 */

		for (i = 1; i < ((union acpi_operand_object *)
				 index_desc->reference.object)->common.
		     reference_count; i++) {
			acpi_ut_add_reference(new_desc);
		}

		break;

	case ACPI_TYPE_BUFFER_FIELD:

		/*
		 * Store into a Buffer or String (not actually a real buffer_field)
		 * at a location defined by an Index.
		 *
		 * The first 8-bit element of the source object is written to the
		 * 8-bit Buffer location defined by the Index destination object,
		 * according to the ACPI 2.0 specification.
		 */

		/*
		 * Make sure the target is a Buffer or String. An error should
		 * not happen here, since the reference_object was constructed
		 * by the INDEX_OP code.
		 */
		obj_desc = index_desc->reference.object;
		if ((obj_desc->common.type != ACPI_TYPE_BUFFER) &&
		    (obj_desc->common.type != ACPI_TYPE_STRING)) {
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}

		/*
		 * The assignment of the individual elements will be slightly
		 * different for each source type.
		 */
		switch (source_desc->common.type) {
		case ACPI_TYPE_INTEGER:

			/* Use the least-significant byte of the integer */

			value = (u8) (source_desc->integer.value);
			break;

		case ACPI_TYPE_BUFFER:
		case ACPI_TYPE_STRING:

			/* Note: Takes advantage of common string/buffer fields */

			value = source_desc->buffer.pointer[0];
			break;

		default:

			/* All other types are invalid */

			ACPI_ERROR((AE_INFO,
				    "Source must be Integer/Buffer/String type, not %s",
				    acpi_ut_get_object_type_name(source_desc)));
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}

		/* Store the source value into the target buffer byte */

		obj_desc->buffer.pointer[index_desc->reference.value] = value;
		break;

	default:
		ACPI_ERROR((AE_INFO, "Target is not a Package or BufferField"));
		status = AE_AML_OPERAND_TYPE;
		break;
	}

	return_ACPI_STATUS(status);
}