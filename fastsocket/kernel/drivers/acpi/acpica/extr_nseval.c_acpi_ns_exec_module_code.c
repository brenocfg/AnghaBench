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
struct TYPE_2__ {int /*<<< orphan*/  aml_start; } ;
union acpi_operand_object {TYPE_1__ method; } ;
struct acpi_evaluate_info {int /*<<< orphan*/  prefix_node; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MEMSET (struct acpi_evaluate_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_attach_object (int /*<<< orphan*/ ,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_detach_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_evaluate (struct acpi_evaluate_info*) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_add_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ns_exec_module_code ; 
 int /*<<< orphan*/  return_VOID ; 

__attribute__((used)) static void
acpi_ns_exec_module_code(union acpi_operand_object *method_obj,
			 struct acpi_evaluate_info *info)
{
	union acpi_operand_object *root_obj;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_exec_module_code);

	/* Initialize the evaluation information block */

	ACPI_MEMSET(info, 0, sizeof(struct acpi_evaluate_info));
	info->prefix_node = acpi_gbl_root_node;

	/*
	 * Get the currently attached root object. Add a reference, because the
	 * ref count will be decreased when the method object is installed to
	 * the root node.
	 */
	root_obj = acpi_ns_get_attached_object(acpi_gbl_root_node);
	acpi_ut_add_reference(root_obj);

	/* Install the method (module-level code) in the root node */

	status = acpi_ns_attach_object(acpi_gbl_root_node, method_obj,
				       ACPI_TYPE_METHOD);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	/* Execute the root node as a control method */

	status = acpi_ns_evaluate(info);

	ACPI_DEBUG_PRINT((ACPI_DB_INIT, "Executed module-level code at %p\n",
			  method_obj->method.aml_start));

	/* Detach the temporary method object */

	acpi_ns_detach_object(acpi_gbl_root_node);

	/* Restore the original root object */

	status =
	    acpi_ns_attach_object(acpi_gbl_root_node, root_obj,
				  ACPI_TYPE_DEVICE);

      exit:
	acpi_ut_remove_reference(root_obj);
	return_VOID;
}