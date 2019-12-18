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
struct TYPE_2__ {scalar_t__ aml_opcode; int flags; } ;
union acpi_parse_object {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int ACPI_PARSEOP_GENERIC ; 
 scalar_t__ AML_INT_RETURN_VALUE_OP ; 
 int /*<<< orphan*/  acpi_gbl_ps_node_cache ; 
 int /*<<< orphan*/  acpi_gbl_ps_node_ext_cache ; 
 int /*<<< orphan*/  acpi_os_release_object (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ps_free_op ; 

void acpi_ps_free_op(union acpi_parse_object *op)
{
	ACPI_FUNCTION_NAME(ps_free_op);

	if (op->common.aml_opcode == AML_INT_RETURN_VALUE_OP) {
		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS, "Free retval op: %p\n",
				  op));
	}

	if (op->common.flags & ACPI_PARSEOP_GENERIC) {
		(void)acpi_os_release_object(acpi_gbl_ps_node_cache, op);
	} else {
		(void)acpi_os_release_object(acpi_gbl_ps_node_ext_cache, op);
	}
}