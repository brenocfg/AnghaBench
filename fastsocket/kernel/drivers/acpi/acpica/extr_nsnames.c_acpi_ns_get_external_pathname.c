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
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_ns_build_external_path (struct acpi_namespace_node*,scalar_t__,char*) ; 
 scalar_t__ acpi_ns_get_pathname_length (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  ns_get_external_pathname ; 
 int /*<<< orphan*/  return_PTR (char*) ; 

char *acpi_ns_get_external_pathname(struct acpi_namespace_node *node)
{
	acpi_status status;
	char *name_buffer;
	acpi_size size;

	ACPI_FUNCTION_TRACE_PTR(ns_get_external_pathname, node);

	/* Calculate required buffer size based on depth below root */

	size = acpi_ns_get_pathname_length(node);
	if (!size) {
		return_PTR(NULL);
	}

	/* Allocate a buffer to be returned to caller */

	name_buffer = ACPI_ALLOCATE_ZEROED(size);
	if (!name_buffer) {
		ACPI_ERROR((AE_INFO, "Could not allocate %u bytes", (u32)size));
		return_PTR(NULL);
	}

	/* Build the path in the allocated buffer */

	status = acpi_ns_build_external_path(node, size, name_buffer);
	if (ACPI_FAILURE(status)) {
		ACPI_FREE(name_buffer);
		return_PTR(NULL);
	}

	return_PTR(name_buffer);
}