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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
union acpi_parse_object {TYPE_1__ named; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ROOT_NAME ; 
 int /*<<< orphan*/  AML_SCOPE_OP ; 
 union acpi_parse_object* acpi_ps_alloc_op (int /*<<< orphan*/ ) ; 

union acpi_parse_object *acpi_ps_create_scope_op(void)
{
	union acpi_parse_object *scope_op;

	scope_op = acpi_ps_alloc_op(AML_SCOPE_OP);
	if (!scope_op) {
		return (NULL);
	}

	scope_op->named.name = ACPI_ROOT_NAME;
	return (scope_op);
}