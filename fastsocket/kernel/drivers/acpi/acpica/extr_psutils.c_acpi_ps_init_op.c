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
struct TYPE_3__ {int /*<<< orphan*/  aml_op_name; int /*<<< orphan*/  aml_opcode; int /*<<< orphan*/  descriptor_type; } ;
union acpi_parse_object {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DESC_TYPE_PARSER ; 
 int /*<<< orphan*/  ACPI_DISASM_ONLY_MEMBERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  ACPI_STRNCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* acpi_ps_get_opcode_info (int /*<<< orphan*/ ) ; 

void acpi_ps_init_op(union acpi_parse_object *op, u16 opcode)
{
	ACPI_FUNCTION_ENTRY();

	op->common.descriptor_type = ACPI_DESC_TYPE_PARSER;
	op->common.aml_opcode = opcode;

	ACPI_DISASM_ONLY_MEMBERS(ACPI_STRNCPY(op->common.aml_op_name,
					      (acpi_ps_get_opcode_info
					       (opcode))->name,
					      sizeof(op->common.aml_op_name)));
}