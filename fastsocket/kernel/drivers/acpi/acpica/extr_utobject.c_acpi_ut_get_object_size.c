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
struct TYPE_2__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  acpi_ut_get_package_object_size (union acpi_operand_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_simple_object_size (union acpi_operand_object*,int /*<<< orphan*/ *) ; 

acpi_status
acpi_ut_get_object_size(union acpi_operand_object *internal_object,
			acpi_size * obj_length)
{
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	if ((ACPI_GET_DESCRIPTOR_TYPE(internal_object) ==
	     ACPI_DESC_TYPE_OPERAND)
	    && (internal_object->common.type == ACPI_TYPE_PACKAGE)) {
		status =
		    acpi_ut_get_package_object_size(internal_object,
						    obj_length);
	} else {
		status =
		    acpi_ut_get_simple_object_size(internal_object, obj_length);
	}

	return (status);
}