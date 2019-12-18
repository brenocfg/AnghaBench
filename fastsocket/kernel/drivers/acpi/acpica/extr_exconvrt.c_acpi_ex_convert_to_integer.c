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
struct TYPE_6__ {size_t value; } ;
struct TYPE_5__ {int type; } ;
struct TYPE_4__ {size_t length; int /*<<< orphan*/ * pointer; } ;
union acpi_operand_object {TYPE_3__ integer; TYPE_2__ common; TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  size_t acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (size_t) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
#define  ACPI_TYPE_BUFFER 130 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_AML_BUFFER_LIMIT ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  acpi_ex_truncate_for32bit_table (union acpi_operand_object*) ; 
 size_t acpi_gbl_integer_byte_width ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int const) ; 
 int /*<<< orphan*/  acpi_ut_strtoul64 (char*,size_t,size_t*) ; 
 int /*<<< orphan*/  ex_convert_to_integer ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_convert_to_integer(union acpi_operand_object *obj_desc,
			   union acpi_operand_object **result_desc, u32 flags)
{
	union acpi_operand_object *return_desc;
	u8 *pointer;
	acpi_integer result;
	u32 i;
	u32 count;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_convert_to_integer, obj_desc);

	switch (obj_desc->common.type) {
	case ACPI_TYPE_INTEGER:

		/* No conversion necessary */

		*result_desc = obj_desc;
		return_ACPI_STATUS(AE_OK);

	case ACPI_TYPE_BUFFER:
	case ACPI_TYPE_STRING:

		/* Note: Takes advantage of common buffer/string fields */

		pointer = obj_desc->buffer.pointer;
		count = obj_desc->buffer.length;
		break;

	default:
		return_ACPI_STATUS(AE_TYPE);
	}

	/*
	 * Convert the buffer/string to an integer. Note that both buffers and
	 * strings are treated as raw data - we don't convert ascii to hex for
	 * strings.
	 *
	 * There are two terminating conditions for the loop:
	 * 1) The size of an integer has been reached, or
	 * 2) The end of the buffer or string has been reached
	 */
	result = 0;

	/* String conversion is different than Buffer conversion */

	switch (obj_desc->common.type) {
	case ACPI_TYPE_STRING:

		/*
		 * Convert string to an integer - for most cases, the string must be
		 * hexadecimal as per the ACPI specification. The only exception (as
		 * of ACPI 3.0) is that the to_integer() operator allows both decimal
		 * and hexadecimal strings (hex prefixed with "0x").
		 */
		status = acpi_ut_strtoul64((char *)pointer, flags, &result);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
		break;

	case ACPI_TYPE_BUFFER:

		/* Check for zero-length buffer */

		if (!count) {
			return_ACPI_STATUS(AE_AML_BUFFER_LIMIT);
		}

		/* Transfer no more than an integer's worth of data */

		if (count > acpi_gbl_integer_byte_width) {
			count = acpi_gbl_integer_byte_width;
		}

		/*
		 * Convert buffer to an integer - we simply grab enough raw data
		 * from the buffer to fill an integer
		 */
		for (i = 0; i < count; i++) {
			/*
			 * Get next byte and shift it into the Result.
			 * Little endian is used, meaning that the first byte of the buffer
			 * is the LSB of the integer
			 */
			result |= (((acpi_integer) pointer[i]) << (i * 8));
		}
		break;

	default:

		/* No other types can get here */
		break;
	}

	/* Create a new integer */

	return_desc = acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
	if (!return_desc) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Converted value: %8.8X%8.8X\n",
			  ACPI_FORMAT_UINT64(result)));

	/* Save the Result */

	return_desc->integer.value = result;
	acpi_ex_truncate_for32bit_table(return_desc);
	*result_desc = return_desc;
	return_ACPI_STATUS(AE_OK);
}