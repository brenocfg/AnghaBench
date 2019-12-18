#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  field_flags; int /*<<< orphan*/  base_byte_offset; int /*<<< orphan*/  start_field_bit_offset; int /*<<< orphan*/  bit_length; } ;
struct TYPE_13__ {scalar_t__ type; int flags; } ;
struct TYPE_12__ {scalar_t__ value; } ;
struct TYPE_11__ {void* pointer; } ;
struct TYPE_10__ {int attribute; int /*<<< orphan*/  bit_length; TYPE_2__* region_obj; } ;
union acpi_operand_object {TYPE_7__ common_field; TYPE_6__ common; TYPE_5__ integer; TYPE_4__ buffer; TYPE_3__ field; } ;
typedef  int u32 ;
struct acpi_walk_state {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;
struct TYPE_8__ {scalar_t__ space_id; } ;
struct TYPE_9__ {TYPE_1__ region; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_IPMI ; 
 scalar_t__ ACPI_ADR_SPACE_SMBUS ; 
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 scalar_t__ ACPI_IPMI_BUFFER_SIZE ; 
 int ACPI_READ ; 
 scalar_t__ ACPI_ROUND_BITS_UP_TO_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SMBUS_BUFFER_SIZE ; 
 scalar_t__ ACPI_TYPE_BUFFER_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_LOCAL_REGION_FIELD ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ds_get_buffer_field_arguments (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ex_access_region (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_ex_acquire_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_extract_from_field (union acpi_operand_object*,void*,int) ; 
 int /*<<< orphan*/  acpi_ex_release_global_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_gbl_integer_byte_width ; 
 int /*<<< orphan*/  acpi_integer ; 
 union acpi_operand_object* acpi_ut_create_buffer_object (scalar_t__) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_read_data_from_field ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_read_data_from_field(struct acpi_walk_state *walk_state,
			     union acpi_operand_object *obj_desc,
			     union acpi_operand_object **ret_buffer_desc)
{
	acpi_status status;
	union acpi_operand_object *buffer_desc;
	acpi_size length;
	void *buffer;
	u32 function;

	ACPI_FUNCTION_TRACE_PTR(ex_read_data_from_field, obj_desc);

	/* Parameter validation */

	if (!obj_desc) {
		return_ACPI_STATUS(AE_AML_NO_OPERAND);
	}
	if (!ret_buffer_desc) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	if (obj_desc->common.type == ACPI_TYPE_BUFFER_FIELD) {
		/*
		 * If the buffer_field arguments have not been previously evaluated,
		 * evaluate them now and save the results.
		 */
		if (!(obj_desc->common.flags & AOPOBJ_DATA_VALID)) {
			status = acpi_ds_get_buffer_field_arguments(obj_desc);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}
		}
	} else if ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
		   (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_SMBUS
		    || obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_IPMI)) {
		/*
		 * This is an SMBus or IPMI read. We must create a buffer to hold
		 * the data and then directly access the region handler.
		 *
		 * Note: Smbus protocol value is passed in upper 16-bits of Function
		 */
		if (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_SMBUS) {
			length = ACPI_SMBUS_BUFFER_SIZE;
			function =
			    ACPI_READ | (obj_desc->field.attribute << 16);
		} else {	/* IPMI */

			length = ACPI_IPMI_BUFFER_SIZE;
			function = ACPI_READ;
		}

		buffer_desc = acpi_ut_create_buffer_object(length);
		if (!buffer_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		/* Lock entire transaction if requested */

		acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

		/* Call the region handler for the read */

		status = acpi_ex_access_region(obj_desc, 0,
					       ACPI_CAST_PTR(acpi_integer,
							     buffer_desc->
							     buffer.pointer),
					       function);
		acpi_ex_release_global_lock(obj_desc->common_field.field_flags);
		goto exit;
	}

	/*
	 * Allocate a buffer for the contents of the field.
	 *
	 * If the field is larger than the size of an acpi_integer, create
	 * a BUFFER to hold it.  Otherwise, use an INTEGER.  This allows
	 * the use of arithmetic operators on the returned value if the
	 * field size is equal or smaller than an Integer.
	 *
	 * Note: Field.length is in bits.
	 */
	length =
	    (acpi_size) ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->field.bit_length);
	if (length > acpi_gbl_integer_byte_width) {

		/* Field is too large for an Integer, create a Buffer instead */

		buffer_desc = acpi_ut_create_buffer_object(length);
		if (!buffer_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}
		buffer = buffer_desc->buffer.pointer;
	} else {
		/* Field will fit within an Integer (normal case) */

		buffer_desc = acpi_ut_create_internal_object(ACPI_TYPE_INTEGER);
		if (!buffer_desc) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		length = acpi_gbl_integer_byte_width;
		buffer_desc->integer.value = 0;
		buffer = &buffer_desc->integer.value;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "FieldRead [TO]:   Obj %p, Type %X, Buf %p, ByteLen %X\n",
			  obj_desc, obj_desc->common.type, buffer,
			  (u32) length));
	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "FieldRead [FROM]: BitLen %X, BitOff %X, ByteOff %X\n",
			  obj_desc->common_field.bit_length,
			  obj_desc->common_field.start_field_bit_offset,
			  obj_desc->common_field.base_byte_offset));

	/* Lock entire transaction if requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Read from the field */

	status = acpi_ex_extract_from_field(obj_desc, buffer, (u32) length);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);

      exit:
	if (ACPI_FAILURE(status)) {
		acpi_ut_remove_reference(buffer_desc);
	} else {
		*ret_buffer_desc = buffer_desc;
	}

	return_ACPI_STATUS(status);
}