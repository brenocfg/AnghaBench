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
struct TYPE_4__ {size_t count; int /*<<< orphan*/  flags; union acpi_operand_object** elements; } ;
union acpi_operand_object {TYPE_2__ package; } ;
struct TYPE_3__ {size_t count; int /*<<< orphan*/ * elements; } ;
union acpi_object {TYPE_1__ package; } ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  acpi_ut_copy_eobject_to_iobject (int /*<<< orphan*/ *,union acpi_operand_object**) ; 
 union acpi_operand_object* acpi_ut_create_package_object (size_t) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_copy_epackage_to_ipackage ; 

__attribute__((used)) static acpi_status
acpi_ut_copy_epackage_to_ipackage(union acpi_object *external_object,
				  union acpi_operand_object **internal_object)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *package_object;
	union acpi_operand_object **package_elements;
	u32 i;

	ACPI_FUNCTION_TRACE(ut_copy_epackage_to_ipackage);

	/* Create the package object */

	package_object =
	    acpi_ut_create_package_object(external_object->package.count);
	if (!package_object) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	package_elements = package_object->package.elements;

	/*
	 * Recursive implementation. Probably ok, since nested external packages
	 * as parameters should be very rare.
	 */
	for (i = 0; i < external_object->package.count; i++) {
		status =
		    acpi_ut_copy_eobject_to_iobject(&external_object->package.
						    elements[i],
						    &package_elements[i]);
		if (ACPI_FAILURE(status)) {

			/* Truncate package and delete it */

			package_object->package.count = i;
			package_elements[i] = NULL;
			acpi_ut_remove_reference(package_object);
			return_ACPI_STATUS(status);
		}
	}

	/* Mark package data valid */

	package_object->package.flags |= AOPOBJ_DATA_VALID;

	*internal_object = package_object;
	return_ACPI_STATUS(status);
}