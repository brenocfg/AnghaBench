#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  union acpi_object {int dummy; } acpi_object ;
struct acpi_pkg_info {int length; int num_packages; scalar_t__ object_space; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int ACPI_ROUND_UP_TO_NATIVE_WORD (int) ; 
 int /*<<< orphan*/  acpi_ut_get_element_length ; 
 int /*<<< orphan*/  acpi_ut_walk_package_tree (union acpi_operand_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_pkg_info*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_get_package_object_size ; 

__attribute__((used)) static acpi_status
acpi_ut_get_package_object_size(union acpi_operand_object *internal_object,
				acpi_size * obj_length)
{
	acpi_status status;
	struct acpi_pkg_info info;

	ACPI_FUNCTION_TRACE_PTR(ut_get_package_object_size, internal_object);

	info.length = 0;
	info.object_space = 0;
	info.num_packages = 1;

	status = acpi_ut_walk_package_tree(internal_object, NULL,
					   acpi_ut_get_element_length, &info);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * We have handled all of the objects in all levels of the package.
	 * just add the length of the package objects themselves.
	 * Round up to the next machine word.
	 */
	info.length += ACPI_ROUND_UP_TO_NATIVE_WORD(sizeof(union acpi_object)) *
	    (acpi_size) info.num_packages;

	/* Return the total package length */

	*obj_length = info.length;
	return_ACPI_STATUS(status);
}