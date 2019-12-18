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
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int flags; scalar_t__ length; int /*<<< orphan*/  address; int /*<<< orphan*/  space_id; struct acpi_namespace_node* node; } ;
struct TYPE_5__ {int /*<<< orphan*/  aml_start; int /*<<< orphan*/  aml_length; } ;
union acpi_operand_object {TYPE_4__ common; TYPE_2__ region; TYPE_1__ extra; } ;
struct TYPE_7__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {TYPE_3__ name; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AOPOBJ_INVALID ; 
 int /*<<< orphan*/  acpi_ds_execute_arguments (struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_os_validate_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_display_init_pathname (int /*<<< orphan*/ ,struct acpi_namespace_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ds_get_region_arguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ds_get_region_arguments(union acpi_operand_object *obj_desc)
{
	struct acpi_namespace_node *node;
	acpi_status status;
	union acpi_operand_object *extra_desc;

	ACPI_FUNCTION_TRACE_PTR(ds_get_region_arguments, obj_desc);

	if (obj_desc->region.flags & AOPOBJ_DATA_VALID) {
		return_ACPI_STATUS(AE_OK);
	}

	extra_desc = acpi_ns_get_secondary_object(obj_desc);
	if (!extra_desc) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Get the Region node */

	node = obj_desc->region.node;

	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_REGION, node, NULL));

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "[%4.4s] OpRegion Arg Init at AML %p\n",
			  acpi_ut_get_node_name(node),
			  extra_desc->extra.aml_start));

	/* Execute the argument AML */

	status = acpi_ds_execute_arguments(node, node->parent,
					   extra_desc->extra.aml_length,
					   extra_desc->extra.aml_start);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Validate the region address/length via the host OS */

	status = acpi_os_validate_address(obj_desc->region.space_id,
					  obj_desc->region.address,
					  (acpi_size) obj_desc->region.length,
					  acpi_ut_get_node_name(node));

	if (ACPI_FAILURE(status)) {
		/*
		 * Invalid address/length. We will emit an error message and mark
		 * the region as invalid, so that it will cause an additional error if
		 * it is ever used. Then return AE_OK.
		 */
		ACPI_EXCEPTION((AE_INFO, status,
				"During address validation of OpRegion [%4.4s]",
				node->name.ascii));
		obj_desc->common.flags |= AOPOBJ_INVALID;
		status = AE_OK;
	}

	return_ACPI_STATUS(status);
}