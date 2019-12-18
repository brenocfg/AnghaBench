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
struct TYPE_3__ {union acpi_parse_object* arg; } ;
struct TYPE_4__ {int /*<<< orphan*/  arg_list_length; union acpi_parse_object* next; union acpi_parse_object* parent; TYPE_1__ value; int /*<<< orphan*/  aml_opcode; } ;
union acpi_parse_object {TYPE_2__ common; } ;
struct acpi_opcode_info {scalar_t__ class; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AML_CLASS_UNKNOWN ; 
 int AML_HAS_ARGS ; 
 struct acpi_opcode_info* acpi_ps_get_opcode_info (int /*<<< orphan*/ ) ; 

void
acpi_ps_append_arg(union acpi_parse_object *op, union acpi_parse_object *arg)
{
	union acpi_parse_object *prev_arg;
	const struct acpi_opcode_info *op_info;

	ACPI_FUNCTION_ENTRY();

	if (!op) {
		return;
	}

	/* Get the info structure for this opcode */

	op_info = acpi_ps_get_opcode_info(op->common.aml_opcode);
	if (op_info->class == AML_CLASS_UNKNOWN) {

		/* Invalid opcode */

		ACPI_ERROR((AE_INFO, "Invalid AML Opcode: 0x%2.2X",
			    op->common.aml_opcode));
		return;
	}

	/* Check if this opcode requires argument sub-objects */

	if (!(op_info->flags & AML_HAS_ARGS)) {

		/* Has no linked argument objects */

		return;
	}

	/* Append the argument to the linked argument list */

	if (op->common.value.arg) {

		/* Append to existing argument list */

		prev_arg = op->common.value.arg;
		while (prev_arg->common.next) {
			prev_arg = prev_arg->common.next;
		}
		prev_arg->common.next = arg;
	} else {
		/* No argument list, this will be the first argument */

		op->common.value.arg = arg;
	}

	/* Set the parent in this arg and any args linked after it */

	while (arg) {
		arg->common.parent = op;
		arg = arg->common.next;

		op->common.arg_list_length++;
	}
}