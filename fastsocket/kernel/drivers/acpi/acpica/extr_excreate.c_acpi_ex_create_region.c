#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct acpi_namespace_node* node; scalar_t__ length; scalar_t__ address; scalar_t__ space_id; } ;
struct TYPE_9__ {scalar_t__* aml_start; int /*<<< orphan*/  aml_length; } ;
struct TYPE_8__ {union acpi_operand_object* next_object; } ;
union acpi_operand_object {TYPE_5__ region; TYPE_4__ extra; TYPE_3__ common; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {TYPE_2__* op; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {struct acpi_namespace_node* node; } ;
struct TYPE_7__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_LOAD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_NUM_PREDEFINED_REGIONS ; 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 scalar_t__ ACPI_USER_REGION_BEGIN ; 
 int /*<<< orphan*/  AE_AML_INVALID_SPACE_ID ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_create_region ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_create_region(u8 * aml_start,
		      u32 aml_length,
		      u8 region_space, struct acpi_walk_state *walk_state)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;
	struct acpi_namespace_node *node;
	union acpi_operand_object *region_obj2;

	ACPI_FUNCTION_TRACE(ex_create_region);

	/* Get the Namespace Node */

	node = walk_state->op->common.node;

	/*
	 * If the region object is already attached to this node,
	 * just return
	 */
	if (acpi_ns_get_attached_object(node)) {
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * Space ID must be one of the predefined IDs, or in the user-defined
	 * range
	 */
	if ((region_space >= ACPI_NUM_PREDEFINED_REGIONS) &&
	    (region_space < ACPI_USER_REGION_BEGIN)) {
		ACPI_ERROR((AE_INFO, "Invalid AddressSpace type %X",
			    region_space));
		return_ACPI_STATUS(AE_AML_INVALID_SPACE_ID);
	}

	ACPI_DEBUG_PRINT((ACPI_DB_LOAD, "Region Type - %s (%X)\n",
			  acpi_ut_get_region_name(region_space), region_space));

	/* Create the region descriptor */

	obj_desc = acpi_ut_create_internal_object(ACPI_TYPE_REGION);
	if (!obj_desc) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	/*
	 * Remember location in AML stream of address & length
	 * operands since they need to be evaluated at run time.
	 */
	region_obj2 = obj_desc->common.next_object;
	region_obj2->extra.aml_start = aml_start;
	region_obj2->extra.aml_length = aml_length;

	/* Init the region from the operands */

	obj_desc->region.space_id = region_space;
	obj_desc->region.address = 0;
	obj_desc->region.length = 0;
	obj_desc->region.node = node;

	/* Install the new region object in the parent Node */

	status = acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_REGION);

      cleanup:

	/* Remove local reference to the object */

	acpi_ut_remove_reference(obj_desc);
	return_ACPI_STATUS(status);
}