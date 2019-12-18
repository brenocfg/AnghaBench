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
struct TYPE_2__ {scalar_t__ bit_length; scalar_t__ access_bit_width; scalar_t__ start_field_bit_offset; scalar_t__ access_byte_width; } ;
union acpi_operand_object {TYPE_1__ common_field; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  char acpi_integer ;

/* Variables and functions */
 void* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (void*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_INTEGER_BIT_SIZE ; 
 char ACPI_INTEGER_MAX ; 
 char ACPI_MASK_BITS_ABOVE (scalar_t__) ; 
 char ACPI_MASK_BITS_BELOW (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_MEMCPY (char*,char*,scalar_t__) ; 
 scalar_t__ ACPI_MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ ACPI_ROUND_BITS_UP_TO_BYTES (scalar_t__) ; 
 scalar_t__ ACPI_ROUND_UP_TO (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  acpi_ex_write_with_update_rule (union acpi_operand_object*,char,char,scalar_t__) ; 
 int /*<<< orphan*/  ex_insert_into_field ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_insert_into_field(union acpi_operand_object *obj_desc,
			  void *buffer, u32 buffer_length)
{
	acpi_status status;
	acpi_integer mask;
	acpi_integer width_mask;
	acpi_integer merged_datum;
	acpi_integer raw_datum = 0;
	u32 field_offset = 0;
	u32 buffer_offset = 0;
	u32 buffer_tail_bits;
	u32 datum_count;
	u32 field_datum_count;
	u32 i;
	u32 required_length;
	void *new_buffer;

	ACPI_FUNCTION_TRACE(ex_insert_into_field);

	/* Validate input buffer */

	new_buffer = NULL;
	required_length =
	    ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->common_field.bit_length);
	/*
	 * We must have a buffer that is at least as long as the field
	 * we are writing to.  This is because individual fields are
	 * indivisible and partial writes are not supported -- as per
	 * the ACPI specification.
	 */
	if (buffer_length < required_length) {

		/* We need to create a new buffer */

		new_buffer = ACPI_ALLOCATE_ZEROED(required_length);
		if (!new_buffer) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		/*
		 * Copy the original data to the new buffer, starting
		 * at Byte zero.  All unused (upper) bytes of the
		 * buffer will be 0.
		 */
		ACPI_MEMCPY((char *)new_buffer, (char *)buffer, buffer_length);
		buffer = new_buffer;
		buffer_length = required_length;
	}

	/*
	 * Create the bitmasks used for bit insertion.
	 * Note: This if/else is used to bypass compiler differences with the
	 * shift operator
	 */
	if (obj_desc->common_field.access_bit_width == ACPI_INTEGER_BIT_SIZE) {
		width_mask = ACPI_INTEGER_MAX;
	} else {
		width_mask =
		    ACPI_MASK_BITS_ABOVE(obj_desc->common_field.
					 access_bit_width);
	}

	mask = width_mask &
	    ACPI_MASK_BITS_BELOW(obj_desc->common_field.start_field_bit_offset);

	/* Compute the number of datums (access width data items) */

	datum_count = ACPI_ROUND_UP_TO(obj_desc->common_field.bit_length,
				       obj_desc->common_field.access_bit_width);

	field_datum_count = ACPI_ROUND_UP_TO(obj_desc->common_field.bit_length +
					     obj_desc->common_field.
					     start_field_bit_offset,
					     obj_desc->common_field.
					     access_bit_width);

	/* Get initial Datum from the input buffer */

	ACPI_MEMCPY(&raw_datum, buffer,
		    ACPI_MIN(obj_desc->common_field.access_byte_width,
			     buffer_length - buffer_offset));

	merged_datum =
	    raw_datum << obj_desc->common_field.start_field_bit_offset;

	/* Write the entire field */

	for (i = 1; i < field_datum_count; i++) {

		/* Write merged datum to the target field */

		merged_datum &= mask;
		status = acpi_ex_write_with_update_rule(obj_desc, mask,
							merged_datum,
							field_offset);
		if (ACPI_FAILURE(status)) {
			goto exit;
		}

		field_offset += obj_desc->common_field.access_byte_width;

		/*
		 * Start new output datum by merging with previous input datum
		 * if necessary.
		 *
		 * Note: Before the shift, check if the shift value will be larger than
		 * the integer size. If so, there is no need to perform the operation.
		 * This avoids the differences in behavior between different compilers
		 * concerning shift values larger than the target data width.
		 */
		if ((obj_desc->common_field.access_bit_width -
		     obj_desc->common_field.start_field_bit_offset) <
		    ACPI_INTEGER_BIT_SIZE) {
			merged_datum =
			    raw_datum >> (obj_desc->common_field.
					  access_bit_width -
					  obj_desc->common_field.
					  start_field_bit_offset);
		} else {
			merged_datum = 0;
		}

		mask = width_mask;

		if (i == datum_count) {
			break;
		}

		/* Get the next input datum from the buffer */

		buffer_offset += obj_desc->common_field.access_byte_width;
		ACPI_MEMCPY(&raw_datum, ((char *)buffer) + buffer_offset,
			    ACPI_MIN(obj_desc->common_field.access_byte_width,
				     buffer_length - buffer_offset));
		merged_datum |=
		    raw_datum << obj_desc->common_field.start_field_bit_offset;
	}

	/* Mask off any extra bits in the last datum */

	buffer_tail_bits = (obj_desc->common_field.bit_length +
			    obj_desc->common_field.start_field_bit_offset) %
	    obj_desc->common_field.access_bit_width;
	if (buffer_tail_bits) {
		mask &= ACPI_MASK_BITS_ABOVE(buffer_tail_bits);
	}

	/* Write the last datum to the field */

	merged_datum &= mask;
	status = acpi_ex_write_with_update_rule(obj_desc,
						mask, merged_datum,
						field_offset);

      exit:
	/* Free temporary buffer if we used one */

	if (new_buffer) {
		ACPI_FREE(new_buffer);
	}
	return_ACPI_STATUS(status);
}