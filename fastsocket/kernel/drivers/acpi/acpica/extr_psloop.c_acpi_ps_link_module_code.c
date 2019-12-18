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
struct TYPE_2__ {int aml_length; union acpi_operand_object* mutex; int /*<<< orphan*/  flags; int /*<<< orphan*/  owner_id; int /*<<< orphan*/ * aml_start; } ;
union acpi_operand_object {TYPE_1__ method; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_owner_id ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AOPOBJ_MODULE_LEVEL ; 
 union acpi_operand_object* acpi_gbl_module_code_list ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_ps_link_module_code(u8 *aml_start, u32 aml_length, acpi_owner_id owner_id)
{
	union acpi_operand_object *prev;
	union acpi_operand_object *next;
	union acpi_operand_object *method_obj;

	/* Get the tail of the list */

	prev = next = acpi_gbl_module_code_list;
	while (next) {
		prev = next;
		next = next->method.mutex;
	}

	/*
	 * Insert the module level code into the list. Merge it if it is
	 * adjacent to the previous element.
	 */
	if (!prev ||
	    ((prev->method.aml_start + prev->method.aml_length) != aml_start)) {

		/* Create, initialize, and link a new temporary method object */

		method_obj = acpi_ut_create_internal_object(ACPI_TYPE_METHOD);
		if (!method_obj) {
			return;
		}

		method_obj->method.aml_start = aml_start;
		method_obj->method.aml_length = aml_length;
		method_obj->method.owner_id = owner_id;
		method_obj->method.flags |= AOPOBJ_MODULE_LEVEL;

		if (!prev) {
			acpi_gbl_module_code_list = method_obj;
		} else {
			prev->method.mutex = method_obj;
		}
	} else {
		prev->method.aml_length += aml_length;
	}
}