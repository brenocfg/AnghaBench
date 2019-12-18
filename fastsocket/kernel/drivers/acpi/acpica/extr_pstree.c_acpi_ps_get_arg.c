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
struct TYPE_4__ {union acpi_parse_object* next; TYPE_1__ value; int /*<<< orphan*/  aml_opcode; } ;
union acpi_parse_object {TYPE_2__ common; } ;
typedef  scalar_t__ u32 ;
struct acpi_opcode_info {scalar_t__ class; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ AML_CLASS_UNKNOWN ; 
 int AML_HAS_ARGS ; 
 struct acpi_opcode_info* acpi_ps_get_opcode_info (int /*<<< orphan*/ ) ; 

union acpi_parse_object *acpi_ps_get_arg(union acpi_parse_object *op, u32 argn)
{
	union acpi_parse_object *arg = NULL;
	const struct acpi_opcode_info *op_info;

	ACPI_FUNCTION_ENTRY();

	/* Get the info structure for this opcode */

	op_info = acpi_ps_get_opcode_info(op->common.aml_opcode);
	if (op_info->class == AML_CLASS_UNKNOWN) {

		/* Invalid opcode or ASCII character */

		return (NULL);
	}

	/* Check if this opcode requires argument sub-objects */

	if (!(op_info->flags & AML_HAS_ARGS)) {

		/* Has no linked argument objects */

		return (NULL);
	}

	/* Get the requested argument object */

	arg = op->common.value.arg;
	while (arg && argn) {
		argn--;
		arg = arg->common.next;
	}

	return (arg);
}