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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
union acpi_operand_object {TYPE_1__ common; } ;

/* Variables and functions */
 char* acpi_ut_get_type_name (int /*<<< orphan*/ ) ; 

char *acpi_ut_get_object_type_name(union acpi_operand_object *obj_desc)
{

	if (!obj_desc) {
		return ("[NULL Object Descriptor]");
	}

	return (acpi_ut_get_type_name(obj_desc->common.type));
}