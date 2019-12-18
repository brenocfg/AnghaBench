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
struct TYPE_2__ {scalar_t__ bit_length; int access_bit_width; scalar_t__ start_field_bit_offset; scalar_t__ access_byte_width; } ;
union acpi_operand_object {TYPE_1__ common_field; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_integer ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_INTEGER_BIT_SIZE ; 
 int ACPI_MASK_BITS_ABOVE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_MEMCPY (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MEMSET (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_READ ; 
 scalar_t__ ACPI_ROUND_BITS_UP_TO_BYTES (scalar_t__) ; 
 scalar_t__ ACPI_ROUND_UP_TO (scalar_t__,int) ; 
 int /*<<< orphan*/  AE_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ex_field_datum_io (union acpi_operand_object*,scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_extract_from_field ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_extract_from_field(union acpi_operand_object *obj_desc,
			   void *buffer, u32 buffer_length)
{
	acpi_status status;
	acpi_integer raw_datum;
	acpi_integer merged_datum;
	u32 field_offset = 0;
	u32 buffer_offset = 0;
	u32 buffer_tail_bits;
	u32 datum_count;
	u32 field_datum_count;
	u32 i;

	ACPI_FUNCTION_TRACE(ex_extract_from_field);

	/* Validate target buffer and clear it */

	if (buffer_length <
	    ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->common_field.bit_length)) {
		ACPI_ERROR((AE_INFO,
			    "Field size %X (bits) is too large for buffer (%X)",
			    obj_desc->common_field.bit_length, buffer_length));

		return_ACPI_STATUS(AE_BUFFER_OVERFLOW);
	}
	ACPI_MEMSET(buffer, 0, buffer_length);

	/* Compute the number of datums (access width data items) */

	datum_count = ACPI_ROUND_UP_TO(obj_desc->common_field.bit_length,
				       obj_desc->common_field.access_bit_width);
	field_datum_count = ACPI_ROUND_UP_TO(obj_desc->common_field.bit_length +
					     obj_desc->common_field.
					     start_field_bit_offset,
					     obj_desc->common_field.
					     access_bit_width);

	/* Priming read from the field */

	status =
	    acpi_ex_field_datum_io(obj_desc, field_offset, &raw_datum,
				   ACPI_READ);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}
	merged_datum =
	    raw_datum >> obj_desc->common_field.start_field_bit_offset;

	/* Read the rest of the field */

	for (i = 1; i < field_datum_count; i++) {

		/* Get next input datum from the field */

		field_offset += obj_desc->common_field.access_byte_width;
		status = acpi_ex_field_datum_io(obj_desc, field_offset,
						&raw_datum, ACPI_READ);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		/*
		 * Merge with previous datum if necessary.
		 *
		 * Note: Before the shift, check if the shift value will be larger than
		 * the integer size. If so, there is no need to perform the operation.
		 * This avoids the differences in behavior between different compilers
		 * concerning shift values larger than the target data width.
		 */
		if ((obj_desc->common_field.access_bit_width -
		     obj_desc->common_field.start_field_bit_offset) <
		    ACPI_INTEGER_BIT_SIZE) {
			merged_datum |=
			    raw_datum << (obj_desc->common_field.
					  access_bit_width -
					  obj_desc->common_field.
					  start_field_bit_offset);
		}

		if (i == datum_count) {
			break;
		}

		/* Write merged datum to target buffer */

		ACPI_MEMCPY(((char *)buffer) + buffer_offset, &merged_datum,
			    ACPI_MIN(obj_desc->common_field.access_byte_width,
				     buffer_length - buffer_offset));

		buffer_offset += obj_desc->common_field.access_byte_width;
		merged_datum =
		    raw_datum >> obj_desc->common_field.start_field_bit_offset;
	}

	/* Mask off any extra bits in the last datum */

	buffer_tail_bits = obj_desc->common_field.bit_length %
	    obj_desc->common_field.access_bit_width;
	if (buffer_tail_bits) {
		merged_datum &= ACPI_MASK_BITS_ABOVE(buffer_tail_bits);
	}

	/* Write the last datum to the buffer */

	ACPI_MEMCPY(((char *)buffer) + buffer_offset, &merged_datum,
		    ACPI_MIN(obj_desc->common_field.access_byte_width,
			     buffer_length - buffer_offset));

	return_ACPI_STATUS(AE_OK);
}