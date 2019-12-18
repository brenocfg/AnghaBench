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
struct TYPE_6__ {scalar_t__ space_id; scalar_t__ length; int /*<<< orphan*/  node; } ;
struct TYPE_5__ {scalar_t__ base_byte_offset; scalar_t__ access_byte_width; int /*<<< orphan*/  node; union acpi_operand_object* region_obj; } ;
struct TYPE_4__ {scalar_t__ type; int flags; } ;
union acpi_operand_object {TYPE_3__ region; TYPE_2__ common_field; TYPE_1__ common; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_IPMI ; 
 scalar_t__ ACPI_ADR_SPACE_SMBUS ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ACPI_ROUND_UP (scalar_t__,scalar_t__) ; 
 scalar_t__ ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_AML_ILLEGAL_ADDRESS ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_AML_REGION_LIMIT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int AOPOBJ_INVALID ; 
 int /*<<< orphan*/  acpi_ds_get_region_arguments (union acpi_operand_object*) ; 
 scalar_t__ acpi_gbl_enable_interpreter_slack ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_setup_region ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ex_setup_region(union acpi_operand_object *obj_desc,
		     u32 field_datum_byte_offset)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *rgn_desc;

	ACPI_FUNCTION_TRACE_U32(ex_setup_region, field_datum_byte_offset);

	rgn_desc = obj_desc->common_field.region_obj;

	/* We must have a valid region */

	if (rgn_desc->common.type != ACPI_TYPE_REGION) {
		ACPI_ERROR((AE_INFO, "Needed Region, found type %X (%s)",
			    rgn_desc->common.type,
			    acpi_ut_get_object_type_name(rgn_desc)));

		return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	}

	/*
	 * If the Region Address and Length have not been previously evaluated,
	 * evaluate them now and save the results.
	 */
	if (!(rgn_desc->common.flags & AOPOBJ_DATA_VALID)) {
		status = acpi_ds_get_region_arguments(rgn_desc);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
	}

	/* Exit if Address/Length have been disallowed by the host OS */

	if (rgn_desc->common.flags & AOPOBJ_INVALID) {
		return_ACPI_STATUS(AE_AML_ILLEGAL_ADDRESS);
	}

	/*
	 * Exit now for SMBus or IPMI address space, it has a non-linear address space
	 * and the request cannot be directly validated
	 */
	if (rgn_desc->region.space_id == ACPI_ADR_SPACE_SMBUS ||
	    rgn_desc->region.space_id == ACPI_ADR_SPACE_IPMI) {

		/* SMBus or IPMI has a non-linear address space */

		return_ACPI_STATUS(AE_OK);
	}
#ifdef ACPI_UNDER_DEVELOPMENT
	/*
	 * If the Field access is any_acc, we can now compute the optimal
	 * access (because we know know the length of the parent region)
	 */
	if (!(obj_desc->common.flags & AOPOBJ_DATA_VALID)) {
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
	}
#endif

	/*
	 * Validate the request.  The entire request from the byte offset for a
	 * length of one field datum (access width) must fit within the region.
	 * (Region length is specified in bytes)
	 */
	if (rgn_desc->region.length <
	    (obj_desc->common_field.base_byte_offset +
	     field_datum_byte_offset +
	     obj_desc->common_field.access_byte_width)) {
		if (acpi_gbl_enable_interpreter_slack) {
			/*
			 * Slack mode only:  We will go ahead and allow access to this
			 * field if it is within the region length rounded up to the next
			 * access width boundary. acpi_size cast for 64-bit compile.
			 */
			if (ACPI_ROUND_UP(rgn_desc->region.length,
					  obj_desc->common_field.
					  access_byte_width) >=
			    ((acpi_size) obj_desc->common_field.
			     base_byte_offset +
			     obj_desc->common_field.access_byte_width +
			     field_datum_byte_offset)) {
				return_ACPI_STATUS(AE_OK);
			}
		}

		if (rgn_desc->region.length <
		    obj_desc->common_field.access_byte_width) {
			/*
			 * This is the case where the access_type (acc_word, etc.) is wider
			 * than the region itself.  For example, a region of length one
			 * byte, and a field with Dword access specified.
			 */
			ACPI_ERROR((AE_INFO,
				    "Field [%4.4s] access width (%d bytes) too large for region [%4.4s] (length %X)",
				    acpi_ut_get_node_name(obj_desc->
							  common_field.node),
				    obj_desc->common_field.access_byte_width,
				    acpi_ut_get_node_name(rgn_desc->region.
							  node),
				    rgn_desc->region.length));
		}

		/*
		 * Offset rounded up to next multiple of field width
		 * exceeds region length, indicate an error
		 */
		ACPI_ERROR((AE_INFO,
			    "Field [%4.4s] Base+Offset+Width %X+%X+%X is beyond end of region [%4.4s] (length %X)",
			    acpi_ut_get_node_name(obj_desc->common_field.node),
			    obj_desc->common_field.base_byte_offset,
			    field_datum_byte_offset,
			    obj_desc->common_field.access_byte_width,
			    acpi_ut_get_node_name(rgn_desc->region.node),
			    rgn_desc->region.length));

		return_ACPI_STATUS(AE_AML_REGION_LIMIT);
	}

	return_ACPI_STATUS(AE_OK);
}