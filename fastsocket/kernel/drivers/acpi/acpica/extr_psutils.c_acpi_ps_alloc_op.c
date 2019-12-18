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
struct TYPE_2__ {scalar_t__ flags; } ;
union acpi_parse_object {TYPE_1__ common; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct acpi_opcode_info {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_PARSEOP_BYTELIST ; 
 scalar_t__ ACPI_PARSEOP_DEFERRED ; 
 scalar_t__ ACPI_PARSEOP_GENERIC ; 
 scalar_t__ ACPI_PARSEOP_NAMED ; 
 int AML_DEFER ; 
 int /*<<< orphan*/  AML_INT_BYTELIST_OP ; 
 int AML_NAMED ; 
 int /*<<< orphan*/  acpi_gbl_ps_node_cache ; 
 int /*<<< orphan*/  acpi_gbl_ps_node_ext_cache ; 
 union acpi_parse_object* acpi_os_acquire_object (int /*<<< orphan*/ ) ; 
 struct acpi_opcode_info* acpi_ps_get_opcode_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_init_op (union acpi_parse_object*,int /*<<< orphan*/ ) ; 

union acpi_parse_object *acpi_ps_alloc_op(u16 opcode)
{
	union acpi_parse_object *op;
	const struct acpi_opcode_info *op_info;
	u8 flags = ACPI_PARSEOP_GENERIC;

	ACPI_FUNCTION_ENTRY();

	op_info = acpi_ps_get_opcode_info(opcode);

	/* Determine type of parse_op required */

	if (op_info->flags & AML_DEFER) {
		flags = ACPI_PARSEOP_DEFERRED;
	} else if (op_info->flags & AML_NAMED) {
		flags = ACPI_PARSEOP_NAMED;
	} else if (opcode == AML_INT_BYTELIST_OP) {
		flags = ACPI_PARSEOP_BYTELIST;
	}

	/* Allocate the minimum required size object */

	if (flags == ACPI_PARSEOP_GENERIC) {

		/* The generic op (default) is by far the most common (16 to 1) */

		op = acpi_os_acquire_object(acpi_gbl_ps_node_cache);
	} else {
		/* Extended parseop */

		op = acpi_os_acquire_object(acpi_gbl_ps_node_ext_cache);
	}

	/* Initialize the Op */

	if (op) {
		acpi_ps_init_op(op, opcode);
		op->common.flags = flags;
	}

	return (op);
}