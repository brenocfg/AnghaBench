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
struct acpi_namespace_node {scalar_t__ type; } ;
struct acpi_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 struct acpi_namespace_node* acpi_ns_map_handle_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_validate_buffer (struct acpi_buffer*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_validate_parameters ; 

__attribute__((used)) static acpi_status
acpi_rs_validate_parameters(acpi_handle device_handle,
			    struct acpi_buffer *buffer,
			    struct acpi_namespace_node **return_node)
{
	acpi_status status;
	struct acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(rs_validate_parameters);

	/*
	 * Must have a valid handle to an ACPI device
	 */
	if (!device_handle) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	node = acpi_ns_map_handle_to_node(device_handle);
	if (!node) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	if (node->type != ACPI_TYPE_DEVICE) {
		return_ACPI_STATUS(AE_TYPE);
	}

	/*
	 * Validate the user buffer object
	 *
	 * if there is a non-zero buffer length we also need a valid pointer in
	 * the buffer. If it's a zero buffer length, we'll be returning the
	 * needed buffer size (later), so keep going.
	 */
	status = acpi_ut_validate_buffer(buffer);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	*return_node = node;
	return_ACPI_STATUS(AE_OK);
}