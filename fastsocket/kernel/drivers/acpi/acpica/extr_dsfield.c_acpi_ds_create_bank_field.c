#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ integer; int /*<<< orphan*/  string; int /*<<< orphan*/  name; union acpi_parse_object* arg; } ;
struct TYPE_4__ {union acpi_parse_object* next; TYPE_1__ value; } ;
union acpi_parse_object {TYPE_2__ common; } ;
typedef  scalar_t__ u8 ;
struct acpi_walk_state {int /*<<< orphan*/  scope_info; } ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_create_field_info {struct acpi_namespace_node* data_register_node; struct acpi_namespace_node* region_node; int /*<<< orphan*/  field_type; scalar_t__ field_flags; struct acpi_namespace_node* register_node; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_NS_SEARCH_PARENT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_BANK_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  acpi_ds_get_field_names (struct acpi_create_field_info*,struct acpi_walk_state*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ns_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_walk_state*,struct acpi_namespace_node**) ; 
 int /*<<< orphan*/  ds_create_bank_field ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_create_bank_field(union acpi_parse_object *op,
			  struct acpi_namespace_node *region_node,
			  struct acpi_walk_state *walk_state)
{
	acpi_status status;
	union acpi_parse_object *arg;
	struct acpi_create_field_info info;

	ACPI_FUNCTION_TRACE_PTR(ds_create_bank_field, op);

	/* First arg is the name of the parent op_region (must already exist) */

	arg = op->common.value.arg;
	if (!region_node) {
		status =
		    acpi_ns_lookup(walk_state->scope_info,
				   arg->common.value.name, ACPI_TYPE_REGION,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT,
				   walk_state, &region_node);
		if (ACPI_FAILURE(status)) {
			ACPI_ERROR_NAMESPACE(arg->common.value.name, status);
			return_ACPI_STATUS(status);
		}
	}

	/* Second arg is the Bank Register (Field) (must already exist) */

	arg = arg->common.next;
	status =
	    acpi_ns_lookup(walk_state->scope_info, arg->common.value.string,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEARCH_PARENT, walk_state,
			   &info.register_node);
	if (ACPI_FAILURE(status)) {
		ACPI_ERROR_NAMESPACE(arg->common.value.string, status);
		return_ACPI_STATUS(status);
	}

	/*
	 * Third arg is the bank_value
	 * This arg is a term_arg, not a constant
	 * It will be evaluated later, by acpi_ds_eval_bank_field_operands
	 */
	arg = arg->common.next;

	/* Fourth arg is the field flags */

	arg = arg->common.next;
	info.field_flags = (u8) arg->common.value.integer;

	/* Each remaining arg is a Named Field */

	info.field_type = ACPI_TYPE_LOCAL_BANK_FIELD;
	info.region_node = region_node;

	/*
	 * Use Info.data_register_node to store bank_field Op
	 * It's safe because data_register_node will never be used when create bank field
	 * We store aml_start and aml_length in the bank_field Op for late evaluation
	 * Used in acpi_ex_prep_field_value(Info)
	 *
	 * TBD: Or, should we add a field in struct acpi_create_field_info, like "void *ParentOp"?
	 */
	info.data_register_node = (struct acpi_namespace_node *)op;

	status = acpi_ds_get_field_names(&info, walk_state, arg->common.next);
	return_ACPI_STATUS(status);
}