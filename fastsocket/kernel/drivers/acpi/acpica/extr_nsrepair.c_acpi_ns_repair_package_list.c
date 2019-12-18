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
struct TYPE_2__ {union acpi_operand_object** elements; } ;
union acpi_operand_object {TYPE_1__ package; } ;
struct acpi_predefined_data {int /*<<< orphan*/  node_flags; int /*<<< orphan*/  pathname; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 union acpi_operand_object* acpi_ut_create_package_object (int) ; 

acpi_status
acpi_ns_repair_package_list(struct acpi_predefined_data *data,
			    union acpi_operand_object **obj_desc_ptr)
{
	union acpi_operand_object *pkg_obj_desc;

	/*
	 * Create the new outer package and populate it. The new package will
	 * have a single element, the lone subpackage.
	 */
	pkg_obj_desc = acpi_ut_create_package_object(1);
	if (!pkg_obj_desc) {
		return (AE_NO_MEMORY);
	}

	pkg_obj_desc->package.elements[0] = *obj_desc_ptr;

	/* Return the new object in the object pointer */

	*obj_desc_ptr = pkg_obj_desc;
	data->flags |= ACPI_OBJECT_REPAIRED;

	ACPI_WARN_PREDEFINED((AE_INFO, data->pathname, data->node_flags,
			      "Incorrectly formed Package, attempting repair"));

	return (AE_OK);
}