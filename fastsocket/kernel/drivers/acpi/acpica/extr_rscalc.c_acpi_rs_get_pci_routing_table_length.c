#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ class; int /*<<< orphan*/  node; } ;
struct TYPE_7__ {scalar_t__ length; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {scalar_t__ count; union acpi_operand_object** elements; } ;
union acpi_operand_object {TYPE_4__ reference; TYPE_3__ string; TYPE_2__ common; TYPE_1__ package; } ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct acpi_pci_routing_table {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_REFCLASS_NAME ; 
 scalar_t__ ACPI_ROUND_UP_TO_64BIT (scalar_t__) ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ acpi_ns_get_pathname_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_get_pci_routing_table_length ; 

acpi_status
acpi_rs_get_pci_routing_table_length(union acpi_operand_object *package_object,
				     acpi_size * buffer_size_needed)
{
	u32 number_of_elements;
	acpi_size temp_size_needed = 0;
	union acpi_operand_object **top_object_list;
	u32 index;
	union acpi_operand_object *package_element;
	union acpi_operand_object **sub_object_list;
	u8 name_found;
	u32 table_index;

	ACPI_FUNCTION_TRACE(rs_get_pci_routing_table_length);

	number_of_elements = package_object->package.count;

	/*
	 * Calculate the size of the return buffer.
	 * The base size is the number of elements * the sizes of the
	 * structures.  Additional space for the strings is added below.
	 * The minus one is to subtract the size of the u8 Source[1]
	 * member because it is added below.
	 *
	 * But each PRT_ENTRY structure has a pointer to a string and
	 * the size of that string must be found.
	 */
	top_object_list = package_object->package.elements;

	for (index = 0; index < number_of_elements; index++) {

		/* Dereference the sub-package */

		package_element = *top_object_list;

		/* We must have a valid Package object */

		if (!package_element ||
		    (package_element->common.type != ACPI_TYPE_PACKAGE)) {
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}

		/*
		 * The sub_object_list will now point to an array of the
		 * four IRQ elements: Address, Pin, Source and source_index
		 */
		sub_object_list = package_element->package.elements;

		/* Scan the irq_table_elements for the Source Name String */

		name_found = FALSE;

		for (table_index = 0; table_index < 4 && !name_found;
		     table_index++) {
			if (*sub_object_list &&	/* Null object allowed */
			    ((ACPI_TYPE_STRING ==
			      (*sub_object_list)->common.type) ||
			     ((ACPI_TYPE_LOCAL_REFERENCE ==
			       (*sub_object_list)->common.type) &&
			      ((*sub_object_list)->reference.class ==
			       ACPI_REFCLASS_NAME)))) {
				name_found = TRUE;
			} else {
				/* Look at the next element */

				sub_object_list++;
			}
		}

		temp_size_needed += (sizeof(struct acpi_pci_routing_table) - 4);

		/* Was a String type found? */

		if (name_found) {
			if ((*sub_object_list)->common.type == ACPI_TYPE_STRING) {
				/*
				 * The length String.Length field does not include the
				 * terminating NULL, add 1
				 */
				temp_size_needed += ((acpi_size)
						     (*sub_object_list)->string.
						     length + 1);
			} else {
				temp_size_needed +=
				    acpi_ns_get_pathname_length((*sub_object_list)->reference.node);
			}
		} else {
			/*
			 * If no name was found, then this is a NULL, which is
			 * translated as a u32 zero.
			 */
			temp_size_needed += sizeof(u32);
		}

		/* Round up the size since each element must be aligned */

		temp_size_needed = ACPI_ROUND_UP_TO_64BIT(temp_size_needed);

		/* Point to the next union acpi_operand_object */

		top_object_list++;
	}

	/*
	 * Add an extra element to the end of the list, essentially a
	 * NULL terminator
	 */
	*buffer_size_needed =
	    temp_size_needed + sizeof(struct acpi_pci_routing_table);
	return_ACPI_STATUS(AE_OK);
}