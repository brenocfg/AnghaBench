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
struct TYPE_8__ {int type; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; scalar_t__ pointer; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pointer; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
union acpi_operand_object {TYPE_4__ common; TYPE_3__ string; TYPE_2__ buffer; TYPE_1__ integer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  ACPI_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_STRNCPY (char*,char*,int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER 130 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_gbl_integer_byte_width ; 
 union acpi_operand_object* acpi_ut_create_buffer_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_convert_to_buffer ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_convert_to_buffer(union acpi_operand_object *obj_desc,
			  union acpi_operand_object **result_desc)
{
	union acpi_operand_object *return_desc;
	u8 *new_buf;

	ACPI_FUNCTION_TRACE_PTR(ex_convert_to_buffer, obj_desc);

	switch (obj_desc->common.type) {
	case ACPI_TYPE_BUFFER:

		/* No conversion necessary */

		*result_desc = obj_desc;
		return_ACPI_STATUS(AE_OK);

	case ACPI_TYPE_INTEGER:

		/*
		 * Create a new Buffer object.
		 * Need enough space for one integer
		 */
		return_desc =
		    acpi_ut_create_buffer_object(acpi_gbl_integer_byte_width);
		if (!return_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		/* Copy the integer to the buffer, LSB first */

		new_buf = return_desc->buffer.pointer;
		ACPI_MEMCPY(new_buf,
			    &obj_desc->integer.value,
			    acpi_gbl_integer_byte_width);
		break;

	case ACPI_TYPE_STRING:

		/*
		 * Create a new Buffer object
		 * Size will be the string length
		 *
		 * NOTE: Add one to the string length to include the null terminator.
		 * The ACPI spec is unclear on this subject, but there is existing
		 * ASL/AML code that depends on the null being transferred to the new
		 * buffer.
		 */
		return_desc = acpi_ut_create_buffer_object((acpi_size)
							   obj_desc->string.
							   length + 1);
		if (!return_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		/* Copy the string to the buffer */

		new_buf = return_desc->buffer.pointer;
		ACPI_STRNCPY((char *)new_buf, (char *)obj_desc->string.pointer,
			     obj_desc->string.length);
		break;

	default:
		return_ACPI_STATUS(AE_TYPE);
	}

	/* Mark buffer initialized */

	return_desc->common.flags |= AOPOBJ_DATA_VALID;
	*result_desc = return_desc;
	return_ACPI_STATUS(AE_OK);
}