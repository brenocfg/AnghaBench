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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct aml_resource_end_tag {int dummy; } ;
typedef  int /*<<< orphan*/  (* acpi_walk_aml_callback ) (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void**) ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_RESOURCE_NAME_END_TAG ; 
 int /*<<< orphan*/  AE_AML_NO_RESOURCE_END_TAG ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_ut_get_descriptor_length (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_ut_get_resource_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_validate_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_walk_aml_resources ; 

acpi_status
acpi_ut_walk_aml_resources(u8 * aml,
			   acpi_size aml_length,
			   acpi_walk_aml_callback user_function, void **context)
{
	acpi_status status;
	u8 *end_aml;
	u8 resource_index;
	u32 length;
	u32 offset = 0;

	ACPI_FUNCTION_TRACE(ut_walk_aml_resources);

	/* The absolute minimum resource template is one end_tag descriptor */

	if (aml_length < sizeof(struct aml_resource_end_tag)) {
		return_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
	}

	/* Point to the end of the resource template buffer */

	end_aml = aml + aml_length;

	/* Walk the byte list, abort on any invalid descriptor type or length */

	while (aml < end_aml) {

		/* Validate the Resource Type and Resource Length */

		status = acpi_ut_validate_resource(aml, &resource_index);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		/* Get the length of this descriptor */

		length = acpi_ut_get_descriptor_length(aml);

		/* Invoke the user function */

		if (user_function) {
			status =
			    user_function(aml, length, offset, resource_index,
					  context);
			if (ACPI_FAILURE(status)) {
				return (status);
			}
		}

		/* An end_tag descriptor terminates this resource template */

		if (acpi_ut_get_resource_type(aml) ==
		    ACPI_RESOURCE_NAME_END_TAG) {
			/*
			 * There must be at least one more byte in the buffer for
			 * the 2nd byte of the end_tag
			 */
			if ((aml + 1) >= end_aml) {
				return_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
			}

			/* Return the pointer to the end_tag if requested */

			if (!user_function) {
				*context = aml;
			}

			/* Normal exit */

			return_ACPI_STATUS(AE_OK);
		}

		aml += length;
		offset += length;
	}

	/* Did not find an end_tag descriptor */

	return (AE_AML_NO_RESOURCE_END_TAG);
}