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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_RESOURCES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MOVE_16_TO_16 (int*,size_t*) ; 
#define  ACPI_RESOURCE_NAME_ADDRESS16 136 
#define  ACPI_RESOURCE_NAME_ADDRESS32 135 
#define  ACPI_RESOURCE_NAME_ADDRESS64 134 
#define  ACPI_RESOURCE_NAME_DMA 133 
#define  ACPI_RESOURCE_NAME_END_TAG 132 
#define  ACPI_RESOURCE_NAME_EXTENDED_IRQ 131 
#define  ACPI_RESOURCE_NAME_IRQ 130 
#define  ACPI_RESOURCE_NAME_VENDOR_LARGE 129 
#define  ACPI_RESOURCE_NAME_VENDOR_SMALL 128 
 scalar_t__ ACPI_ROUND_UP_TO_NATIVE_WORD (int) ; 
 int /*<<< orphan*/  ACPI_RS_SIZE_MIN ; 
 int /*<<< orphan*/  AE_AML_NO_RESOURCE_END_TAG ; 
 int /*<<< orphan*/  AE_OK ; 
 size_t* acpi_gbl_resource_aml_sizes ; 
 int* acpi_gbl_resource_struct_sizes ; 
 int acpi_rs_count_set_bits (size_t) ; 
 int acpi_rs_stream_option_length (int,size_t) ; 
 int /*<<< orphan*/  acpi_ut_get_descriptor_length (size_t*) ; 
 int acpi_ut_get_resource_header_length (size_t*) ; 
 int acpi_ut_get_resource_length (size_t*) ; 
 int acpi_ut_get_resource_type (size_t*) ; 
 int /*<<< orphan*/  acpi_ut_validate_resource (size_t*,size_t*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_get_list_length ; 

acpi_status
acpi_rs_get_list_length(u8 * aml_buffer,
			u32 aml_buffer_length, acpi_size * size_needed)
{
	acpi_status status;
	u8 *end_aml;
	u8 *buffer;
	u32 buffer_size;
	u16 temp16;
	u16 resource_length;
	u32 extra_struct_bytes;
	u8 resource_index;
	u8 minimum_aml_resource_length;

	ACPI_FUNCTION_TRACE(rs_get_list_length);

	*size_needed = 0;
	end_aml = aml_buffer + aml_buffer_length;

	/* Walk the list of AML resource descriptors */

	while (aml_buffer < end_aml) {

		/* Validate the Resource Type and Resource Length */

		status = acpi_ut_validate_resource(aml_buffer, &resource_index);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		/* Get the resource length and base (minimum) AML size */

		resource_length = acpi_ut_get_resource_length(aml_buffer);
		minimum_aml_resource_length =
		    acpi_gbl_resource_aml_sizes[resource_index];

		/*
		 * Augment the size for descriptors with optional
		 * and/or variable length fields
		 */
		extra_struct_bytes = 0;
		buffer =
		    aml_buffer + acpi_ut_get_resource_header_length(aml_buffer);

		switch (acpi_ut_get_resource_type(aml_buffer)) {
		case ACPI_RESOURCE_NAME_IRQ:
			/*
			 * IRQ Resource:
			 * Get the number of bits set in the 16-bit IRQ mask
			 */
			ACPI_MOVE_16_TO_16(&temp16, buffer);
			extra_struct_bytes = acpi_rs_count_set_bits(temp16);
			break;

		case ACPI_RESOURCE_NAME_DMA:
			/*
			 * DMA Resource:
			 * Get the number of bits set in the 8-bit DMA mask
			 */
			extra_struct_bytes = acpi_rs_count_set_bits(*buffer);
			break;

		case ACPI_RESOURCE_NAME_VENDOR_SMALL:
		case ACPI_RESOURCE_NAME_VENDOR_LARGE:
			/*
			 * Vendor Resource:
			 * Get the number of vendor data bytes
			 */
			extra_struct_bytes = resource_length;
			break;

		case ACPI_RESOURCE_NAME_END_TAG:
			/*
			 * End Tag:
			 * This is the normal exit, add size of end_tag
			 */
			*size_needed += ACPI_RS_SIZE_MIN;
			return_ACPI_STATUS(AE_OK);

		case ACPI_RESOURCE_NAME_ADDRESS32:
		case ACPI_RESOURCE_NAME_ADDRESS16:
		case ACPI_RESOURCE_NAME_ADDRESS64:
			/*
			 * Address Resource:
			 * Add the size of the optional resource_source
			 */
			extra_struct_bytes =
			    acpi_rs_stream_option_length(resource_length,
							 minimum_aml_resource_length);
			break;

		case ACPI_RESOURCE_NAME_EXTENDED_IRQ:
			/*
			 * Extended IRQ Resource:
			 * Using the interrupt_table_length, add 4 bytes for each additional
			 * interrupt. Note: at least one interrupt is required and is
			 * included in the minimum descriptor size (reason for the -1)
			 */
			extra_struct_bytes = (buffer[1] - 1) * sizeof(u32);

			/* Add the size of the optional resource_source */

			extra_struct_bytes +=
			    acpi_rs_stream_option_length(resource_length -
							 extra_struct_bytes,
							 minimum_aml_resource_length);
			break;

		default:
			break;
		}

		/*
		 * Update the required buffer size for the internal descriptor structs
		 *
		 * Important: Round the size up for the appropriate alignment. This
		 * is a requirement on IA64.
		 */
		buffer_size = acpi_gbl_resource_struct_sizes[resource_index] +
		    extra_struct_bytes;
		buffer_size = (u32) ACPI_ROUND_UP_TO_NATIVE_WORD(buffer_size);

		*size_needed += buffer_size;

		ACPI_DEBUG_PRINT((ACPI_DB_RESOURCES,
				  "Type %.2X, AmlLength %.2X InternalLength %.2X\n",
				  acpi_ut_get_resource_type(aml_buffer),
				  acpi_ut_get_descriptor_length(aml_buffer),
				  buffer_size));

		/*
		 * Point to the next resource within the AML stream using the length
		 * contained in the resource descriptor header
		 */
		aml_buffer += acpi_ut_get_descriptor_length(aml_buffer);
	}

	/* Did not find an end_tag resource descriptor */

	return_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
}