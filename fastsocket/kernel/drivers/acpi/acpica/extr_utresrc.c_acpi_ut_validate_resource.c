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
typedef  int u8 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_rs_length ;

/* Variables and functions */
#define  ACPI_FIXED_LENGTH 130 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int ACPI_GET8 (void*) ; 
 int ACPI_RESOURCE_NAME_LARGE ; 
 int ACPI_RESOURCE_NAME_LARGE_MAX ; 
 int ACPI_RESOURCE_NAME_SMALL_MASK ; 
#define  ACPI_SMALL_VARIABLE_LENGTH 129 
#define  ACPI_VARIABLE_LENGTH 128 
 int /*<<< orphan*/  AE_AML_BAD_RESOURCE_LENGTH ; 
 int /*<<< orphan*/  AE_AML_INVALID_RESOURCE_TYPE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/ * acpi_gbl_resource_aml_sizes ; 
 int* acpi_gbl_resource_types ; 
 int /*<<< orphan*/  acpi_ut_get_resource_length (void*) ; 

acpi_status acpi_ut_validate_resource(void *aml, u8 * return_index)
{
	u8 resource_type;
	u8 resource_index;
	acpi_rs_length resource_length;
	acpi_rs_length minimum_resource_length;

	ACPI_FUNCTION_ENTRY();

	/*
	 * 1) Validate the resource_type field (Byte 0)
	 */
	resource_type = ACPI_GET8(aml);

	/*
	 * Byte 0 contains the descriptor name (Resource Type)
	 * Examine the large/small bit in the resource header
	 */
	if (resource_type & ACPI_RESOURCE_NAME_LARGE) {

		/* Verify the large resource type (name) against the max */

		if (resource_type > ACPI_RESOURCE_NAME_LARGE_MAX) {
			return (AE_AML_INVALID_RESOURCE_TYPE);
		}

		/*
		 * Large Resource Type -- bits 6:0 contain the name
		 * Translate range 0x80-0x8B to index range 0x10-0x1B
		 */
		resource_index = (u8) (resource_type - 0x70);
	} else {
		/*
		 * Small Resource Type -- bits 6:3 contain the name
		 * Shift range to index range 0x00-0x0F
		 */
		resource_index = (u8)
		    ((resource_type & ACPI_RESOURCE_NAME_SMALL_MASK) >> 3);
	}

	/* Check validity of the resource type, zero indicates name is invalid */

	if (!acpi_gbl_resource_types[resource_index]) {
		return (AE_AML_INVALID_RESOURCE_TYPE);
	}

	/*
	 * 2) Validate the resource_length field. This ensures that the length
	 *    is at least reasonable, and guarantees that it is non-zero.
	 */
	resource_length = acpi_ut_get_resource_length(aml);
	minimum_resource_length = acpi_gbl_resource_aml_sizes[resource_index];

	/* Validate based upon the type of resource - fixed length or variable */

	switch (acpi_gbl_resource_types[resource_index]) {
	case ACPI_FIXED_LENGTH:

		/* Fixed length resource, length must match exactly */

		if (resource_length != minimum_resource_length) {
			return (AE_AML_BAD_RESOURCE_LENGTH);
		}
		break;

	case ACPI_VARIABLE_LENGTH:

		/* Variable length resource, length must be at least the minimum */

		if (resource_length < minimum_resource_length) {
			return (AE_AML_BAD_RESOURCE_LENGTH);
		}
		break;

	case ACPI_SMALL_VARIABLE_LENGTH:

		/* Small variable length resource, length can be (Min) or (Min-1) */

		if ((resource_length > minimum_resource_length) ||
		    (resource_length < (minimum_resource_length - 1))) {
			return (AE_AML_BAD_RESOURCE_LENGTH);
		}
		break;

	default:

		/* Shouldn't happen (because of validation earlier), but be sure */

		return (AE_AML_INVALID_RESOURCE_TYPE);
	}

	/* Optionally return the resource table index */

	if (return_index) {
		*return_index = resource_index;
	}

	return (AE_OK);
}