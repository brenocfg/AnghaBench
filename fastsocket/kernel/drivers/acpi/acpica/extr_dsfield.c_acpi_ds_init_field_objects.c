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
struct TYPE_4__ {scalar_t__ aml_opcode; union acpi_parse_object* next; struct acpi_namespace_node* node; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
union acpi_parse_object {TYPE_2__ common; TYPE_1__ named; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct acpi_walk_state {int parse_flags; int opcode; int /*<<< orphan*/  scope_info; scalar_t__ method_node; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (char*,scalar_t__) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_ERROR_IF_FOUND ; 
 int ACPI_NS_NO_UPSEARCH ; 
 int ACPI_NS_TEMPORARY ; 
 int ACPI_PARSE_DEFERRED_OP ; 
 int ACPI_PARSE_EXECUTE ; 
 int ACPI_PARSE_MODULE_LEVEL ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_BANK_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_INDEX_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REGION_FIELD ; 
 scalar_t__ AE_ALREADY_EXISTS ; 
 scalar_t__ AE_AML_INTERNAL ; 
 scalar_t__ AE_BAD_PARAMETER ; 
 scalar_t__ AE_OK ; 
#define  AML_BANK_FIELD_OP 130 
#define  AML_FIELD_OP 129 
#define  AML_INDEX_FIELD_OP 128 
 scalar_t__ AML_INT_NAMEDFIELD_OP ; 
 scalar_t__ acpi_ns_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct acpi_walk_state*,struct acpi_namespace_node**) ; 
 union acpi_parse_object* acpi_ps_get_arg (union acpi_parse_object*,int) ; 
 int /*<<< orphan*/  ds_init_field_objects ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status
acpi_ds_init_field_objects(union acpi_parse_object *op,
			   struct acpi_walk_state *walk_state)
{
	acpi_status status;
	union acpi_parse_object *arg = NULL;
	struct acpi_namespace_node *node;
	u8 type = 0;
	u32 flags;

	ACPI_FUNCTION_TRACE_PTR(ds_init_field_objects, op);

	/* Execute flag should always be set when this function is entered */

	if (!(walk_state->parse_flags & ACPI_PARSE_EXECUTE)) {
		if (walk_state->parse_flags & ACPI_PARSE_DEFERRED_OP) {

			/* bank_field Op is deferred, just return OK */

			return_ACPI_STATUS(AE_OK);
		}

		return_ACPI_STATUS(AE_AML_INTERNAL);
	}

	/*
	 * Get the field_list argument for this opcode. This is the start of the
	 * list of field elements.
	 */
	switch (walk_state->opcode) {
	case AML_FIELD_OP:
		arg = acpi_ps_get_arg(op, 2);
		type = ACPI_TYPE_LOCAL_REGION_FIELD;
		break;

	case AML_BANK_FIELD_OP:
		arg = acpi_ps_get_arg(op, 4);
		type = ACPI_TYPE_LOCAL_BANK_FIELD;
		break;

	case AML_INDEX_FIELD_OP:
		arg = acpi_ps_get_arg(op, 3);
		type = ACPI_TYPE_LOCAL_INDEX_FIELD;
		break;

	default:
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Creating new namespace node(s), should not already exist */

	flags = ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE |
	    ACPI_NS_ERROR_IF_FOUND;

	/*
	 * Mark node(s) temporary if we are executing a normal control
	 * method. (Don't mark if this is a module-level code method)
	 */
	if (walk_state->method_node &&
	    !(walk_state->parse_flags & ACPI_PARSE_MODULE_LEVEL)) {
		flags |= ACPI_NS_TEMPORARY;
	}

	/*
	 * Walk the list of entries in the field_list
	 * Note: field_list can be of zero length. In this case, Arg will be NULL.
	 */
	while (arg) {
		/*
		 * Ignore OFFSET and ACCESSAS terms here; we are only interested in the
		 * field names in order to enter them into the namespace.
		 */
		if (arg->common.aml_opcode == AML_INT_NAMEDFIELD_OP) {
			status = acpi_ns_lookup(walk_state->scope_info,
						(char *)&arg->named.name, type,
						ACPI_IMODE_LOAD_PASS1, flags,
						walk_state, &node);
			if (ACPI_FAILURE(status)) {
				ACPI_ERROR_NAMESPACE((char *)&arg->named.name,
						     status);
				if (status != AE_ALREADY_EXISTS) {
					return_ACPI_STATUS(status);
				}

				/* Name already exists, just ignore this error */

				status = AE_OK;
			}

			arg->common.node = node;
		}

		/* Get the next field element in the list */

		arg = arg->common.next;
	}

	return_ACPI_STATUS(AE_OK);
}