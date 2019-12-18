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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {struct acpi_namespace_node* parent; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (char*,int /*<<< orphan*/ *) ; 
 int ACPI_NAME_SIZE ; 
 char ACPI_PATH_SEPARATOR ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 char AML_ROOT_PREFIX ; 
 struct acpi_namespace_node* acpi_gbl_root_node ; 

acpi_status
acpi_ns_build_external_path(struct acpi_namespace_node *node,
			    acpi_size size, char *name_buffer)
{
	acpi_size index;
	struct acpi_namespace_node *parent_node;

	ACPI_FUNCTION_ENTRY();

	/* Special case for root */

	index = size - 1;
	if (index < ACPI_NAME_SIZE) {
		name_buffer[0] = AML_ROOT_PREFIX;
		name_buffer[1] = 0;
		return (AE_OK);
	}

	/* Store terminator byte, then build name backwards */

	parent_node = node;
	name_buffer[index] = 0;

	while ((index > ACPI_NAME_SIZE) && (parent_node != acpi_gbl_root_node)) {
		index -= ACPI_NAME_SIZE;

		/* Put the name into the buffer */

		ACPI_MOVE_32_TO_32((name_buffer + index), &parent_node->name);
		parent_node = parent_node->parent;

		/* Prefix name with the path separator */

		index--;
		name_buffer[index] = ACPI_PATH_SEPARATOR;
	}

	/* Overwrite final separator with the root prefix character */

	name_buffer[index] = AML_ROOT_PREFIX;

	if (index != 0) {
		ACPI_ERROR((AE_INFO,
			    "Could not construct external pathname; index=%X, size=%X, Path=%s",
			    (u32) index, (u32) size, &name_buffer[size]));

		return (AE_BAD_PARAMETER);
	}

	return (AE_OK);
}