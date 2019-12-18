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
struct acpi_namespace_node {int dummy; } ;
struct acpi_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct acpi_buffer*)) ; 
 int /*<<< orphan*/  acpi_rs_get_prt_method_data (struct acpi_namespace_node*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_rs_validate_parameters (int /*<<< orphan*/ ,struct acpi_buffer*,struct acpi_namespace_node**) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_get_irq_routing_table(acpi_handle device_handle,
			   struct acpi_buffer *ret_buffer)
{
	acpi_status status;
	struct acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(acpi_get_irq_routing_table);

	/* Validate parameters then dispatch to internal routine */

	status = acpi_rs_validate_parameters(device_handle, ret_buffer, &node);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	status = acpi_rs_get_prt_method_data(node, ret_buffer);
	return_ACPI_STATUS(status);
}