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
struct TYPE_2__ {void* base_byte_offset; void* start_field_bit_offset; void* access_bit_width; void* access_byte_width; void* bit_length; void* attribute; void* field_flags; } ;
union acpi_operand_object {TYPE_1__ common_field; } ;
typedef  void* u8 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_DIV_8 (void*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 void* ACPI_MUL_8 (void*) ; 
 void* ACPI_ROUND_BITS_DOWN_TO_BYTES (void*) ; 
 scalar_t__ ACPI_ROUND_DOWN (void*,void*) ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_OK ; 
 void* acpi_ex_decode_field_access (union acpi_operand_object*,void*,void**) ; 
 int /*<<< orphan*/  ex_prep_common_field_object ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_prep_common_field_object(union acpi_operand_object *obj_desc,
				 u8 field_flags,
				 u8 field_attribute,
				 u32 field_bit_position, u32 field_bit_length)
{
	u32 access_bit_width;
	u32 byte_alignment;
	u32 nearest_byte_address;

	ACPI_FUNCTION_TRACE(ex_prep_common_field_object);

	/*
	 * Note: the structure being initialized is the
	 * ACPI_COMMON_FIELD_INFO;  No structure fields outside of the common
	 * area are initialized by this procedure.
	 */
	obj_desc->common_field.field_flags = field_flags;
	obj_desc->common_field.attribute = field_attribute;
	obj_desc->common_field.bit_length = field_bit_length;

	/*
	 * Decode the access type so we can compute offsets.  The access type gives
	 * two pieces of information - the width of each field access and the
	 * necessary byte_alignment (address granularity) of the access.
	 *
	 * For any_acc, the access_bit_width is the largest width that is both
	 * necessary and possible in an attempt to access the whole field in one
	 * I/O operation.  However, for any_acc, the byte_alignment is always one
	 * byte.
	 *
	 * For all Buffer Fields, the byte_alignment is always one byte.
	 *
	 * For all other access types (Byte, Word, Dword, Qword), the Bitwidth is
	 * the same (equivalent) as the byte_alignment.
	 */
	access_bit_width = acpi_ex_decode_field_access(obj_desc, field_flags,
						       &byte_alignment);
	if (!access_bit_width) {
		return_ACPI_STATUS(AE_AML_OPERAND_VALUE);
	}

	/* Setup width (access granularity) fields */

	obj_desc->common_field.access_byte_width = (u8)
	    ACPI_DIV_8(access_bit_width);	/* 1,  2,  4,  8 */

	obj_desc->common_field.access_bit_width = (u8) access_bit_width;

	/*
	 * base_byte_offset is the address of the start of the field within the
	 * region.  It is the byte address of the first *datum* (field-width data
	 * unit) of the field. (i.e., the first datum that contains at least the
	 * first *bit* of the field.)
	 *
	 * Note: byte_alignment is always either equal to the access_bit_width or 8
	 * (Byte access), and it defines the addressing granularity of the parent
	 * region or buffer.
	 */
	nearest_byte_address =
	    ACPI_ROUND_BITS_DOWN_TO_BYTES(field_bit_position);
	obj_desc->common_field.base_byte_offset = (u32)
	    ACPI_ROUND_DOWN(nearest_byte_address, byte_alignment);

	/*
	 * start_field_bit_offset is the offset of the first bit of the field within
	 * a field datum.
	 */
	obj_desc->common_field.start_field_bit_offset = (u8)
	    (field_bit_position -
	     ACPI_MUL_8(obj_desc->common_field.base_byte_offset));

	return_ACPI_STATUS(AE_OK);
}