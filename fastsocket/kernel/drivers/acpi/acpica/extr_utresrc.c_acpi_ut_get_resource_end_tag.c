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
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * pointer; } ;
union acpi_operand_object {TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ut_walk_aml_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_get_resource_end_tag ; 

acpi_status
acpi_ut_get_resource_end_tag(union acpi_operand_object * obj_desc,
			     u8 ** end_tag)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_get_resource_end_tag);

	/* Allow a buffer length of zero */

	if (!obj_desc->buffer.length) {
		*end_tag = obj_desc->buffer.pointer;
		return_ACPI_STATUS(AE_OK);
	}

	/* Validate the template and get a pointer to the end_tag */

	status = acpi_ut_walk_aml_resources(obj_desc->buffer.pointer,
					    obj_desc->buffer.length, NULL,
					    (void **)end_tag);

	return_ACPI_STATUS(status);
}