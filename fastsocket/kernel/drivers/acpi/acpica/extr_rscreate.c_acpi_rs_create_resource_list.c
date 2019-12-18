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
struct TYPE_2__ {int /*<<< orphan*/ * pointer; int /*<<< orphan*/  length; } ;
union acpi_operand_object {TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_buffer {scalar_t__ length; void* pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_rs_convert_aml_to_resources ; 
 int /*<<< orphan*/  acpi_rs_get_list_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_ut_initialize_buffer (struct acpi_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_walk_aml_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_create_resource_list ; 

acpi_status
acpi_rs_create_resource_list(union acpi_operand_object *aml_buffer,
			     struct acpi_buffer *output_buffer)
{

	acpi_status status;
	u8 *aml_start;
	acpi_size list_size_needed = 0;
	u32 aml_buffer_length;
	void *resource;

	ACPI_FUNCTION_TRACE(rs_create_resource_list);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "AmlBuffer = %p\n", aml_buffer));

	/* Params already validated, so we don't re-validate here */

	aml_buffer_length = aml_buffer->buffer.length;
	aml_start = aml_buffer->buffer.pointer;

	/*
	 * Pass the aml_buffer into a module that can calculate
	 * the buffer size needed for the linked list
	 */
	status = acpi_rs_get_list_length(aml_start, aml_buffer_length,
					 &list_size_needed);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Status=%X ListSizeNeeded=%X\n",
			  status, (u32) list_size_needed));
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Validate/Allocate/Clear caller buffer */

	status = acpi_ut_initialize_buffer(output_buffer, list_size_needed);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Do the conversion */

	resource = output_buffer->pointer;
	status = acpi_ut_walk_aml_resources(aml_start, aml_buffer_length,
					    acpi_rs_convert_aml_to_resources,
					    &resource);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "OutputBuffer %p Length %X\n",
			  output_buffer->pointer, (u32) output_buffer->length));
	return_ACPI_STATUS(AE_OK);
}