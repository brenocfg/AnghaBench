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
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_size ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EBDA_PTR_LENGTH ; 
 scalar_t__ ACPI_EBDA_PTR_LOCATION ; 
 int /*<<< orphan*/  ACPI_EBDA_WINDOW_SIZE ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (int*)) ; 
 scalar_t__ ACPI_HI_RSDP_WINDOW_BASE ; 
 int /*<<< orphan*/  ACPI_HI_RSDP_WINDOW_SIZE ; 
 int /*<<< orphan*/  ACPI_MOVE_16_TO_32 (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_PTR_DIFF (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/ * acpi_os_map_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_unmap_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * acpi_tb_scan_memory_for_rsdp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_find_root_pointer(acpi_size *table_address)
{
	u8 *table_ptr;
	u8 *mem_rover;
	u32 physical_address;

	ACPI_FUNCTION_TRACE(acpi_find_root_pointer);

	/* 1a) Get the location of the Extended BIOS Data Area (EBDA) */

	table_ptr = acpi_os_map_memory((acpi_physical_address)
				       ACPI_EBDA_PTR_LOCATION,
				       ACPI_EBDA_PTR_LENGTH);
	if (!table_ptr) {
		ACPI_ERROR((AE_INFO,
			    "Could not map memory at %8.8X for length %X",
			    ACPI_EBDA_PTR_LOCATION, ACPI_EBDA_PTR_LENGTH));

		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	ACPI_MOVE_16_TO_32(&physical_address, table_ptr);

	/* Convert segment part to physical address */

	physical_address <<= 4;
	acpi_os_unmap_memory(table_ptr, ACPI_EBDA_PTR_LENGTH);

	/* EBDA present? */

	if (physical_address > 0x400) {
		/*
		 * 1b) Search EBDA paragraphs (EBDA is required to be a
		 *     minimum of 1_k length)
		 */
		table_ptr = acpi_os_map_memory((acpi_physical_address)
					       physical_address,
					       ACPI_EBDA_WINDOW_SIZE);
		if (!table_ptr) {
			ACPI_ERROR((AE_INFO,
				    "Could not map memory at %8.8X for length %X",
				    physical_address, ACPI_EBDA_WINDOW_SIZE));

			return_ACPI_STATUS(AE_NO_MEMORY);
		}

		mem_rover =
		    acpi_tb_scan_memory_for_rsdp(table_ptr,
						 ACPI_EBDA_WINDOW_SIZE);
		acpi_os_unmap_memory(table_ptr, ACPI_EBDA_WINDOW_SIZE);

		if (mem_rover) {

			/* Return the physical address */

			physical_address +=
			    (u32) ACPI_PTR_DIFF(mem_rover, table_ptr);

			*table_address = physical_address;
			return_ACPI_STATUS(AE_OK);
		}
	}

	/*
	 * 2) Search upper memory: 16-byte boundaries in E0000h-FFFFFh
	 */
	table_ptr = acpi_os_map_memory((acpi_physical_address)
				       ACPI_HI_RSDP_WINDOW_BASE,
				       ACPI_HI_RSDP_WINDOW_SIZE);

	if (!table_ptr) {
		ACPI_ERROR((AE_INFO,
			    "Could not map memory at %8.8X for length %X",
			    ACPI_HI_RSDP_WINDOW_BASE,
			    ACPI_HI_RSDP_WINDOW_SIZE));

		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	mem_rover =
	    acpi_tb_scan_memory_for_rsdp(table_ptr, ACPI_HI_RSDP_WINDOW_SIZE);
	acpi_os_unmap_memory(table_ptr, ACPI_HI_RSDP_WINDOW_SIZE);

	if (mem_rover) {

		/* Return the physical address */

		physical_address = (u32)
		    (ACPI_HI_RSDP_WINDOW_BASE +
		     ACPI_PTR_DIFF(mem_rover, table_ptr));

		*table_address = physical_address;
		return_ACPI_STATUS(AE_OK);
	}

	/* A valid RSDP was not found */

	ACPI_ERROR((AE_INFO, "A valid RSDP was not found"));
	return_ACPI_STATUS(AE_NOT_FOUND);
}