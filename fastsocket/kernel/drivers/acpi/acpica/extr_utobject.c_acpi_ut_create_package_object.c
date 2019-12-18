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
struct TYPE_2__ {union acpi_operand_object** elements; scalar_t__ count; } ;
union acpi_operand_object {TYPE_1__ package; } ;
typedef  scalar_t__ u32 ;
typedef  int acpi_size ;

/* Variables and functions */
 union acpi_operand_object** ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_PTR (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ut_create_package_object ; 

union acpi_operand_object *acpi_ut_create_package_object(u32 count)
{
	union acpi_operand_object *package_desc;
	union acpi_operand_object **package_elements;

	ACPI_FUNCTION_TRACE_U32(ut_create_package_object, count);

	/* Create a new Package object */

	package_desc = acpi_ut_create_internal_object(ACPI_TYPE_PACKAGE);
	if (!package_desc) {
		return_PTR(NULL);
	}

	/*
	 * Create the element array. Count+1 allows the array to be null
	 * terminated.
	 */
	package_elements = ACPI_ALLOCATE_ZEROED(((acpi_size) count +
						 1) * sizeof(void *));
	if (!package_elements) {
		acpi_ut_remove_reference(package_desc);
		return_PTR(NULL);
	}

	package_desc->package.count = count;
	package_desc->package.elements = package_elements;
	return_PTR(package_desc);
}