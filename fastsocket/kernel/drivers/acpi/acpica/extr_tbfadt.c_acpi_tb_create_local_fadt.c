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
typedef  int u32 ;
struct acpi_table_header {int /*<<< orphan*/  revision; } ;
struct acpi_table_fadt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_MEMCPY (int /*<<< orphan*/ *,struct acpi_table_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MEMSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ACPI_MIN (int,int) ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_tb_convert_fadt () ; 
 int /*<<< orphan*/  acpi_tb_setup_fadt_registers () ; 
 int /*<<< orphan*/  acpi_tb_validate_fadt () ; 

void acpi_tb_create_local_fadt(struct acpi_table_header *table, u32 length)
{
	/*
	 * Check if the FADT is larger than the largest table that we expect
	 * (the ACPI 2.0/3.0 version). If so, truncate the table, and issue
	 * a warning.
	 */
	if (length > sizeof(struct acpi_table_fadt)) {
		ACPI_WARNING((AE_INFO,
			      "FADT (revision %u) is longer than ACPI 2.0 version, "
			      "truncating length 0x%X to 0x%X",
			      table->revision, length,
			      (u32)sizeof(struct acpi_table_fadt)));
	}

	/* Clear the entire local FADT */

	ACPI_MEMSET(&acpi_gbl_FADT, 0, sizeof(struct acpi_table_fadt));

	/* Copy the original FADT, up to sizeof (struct acpi_table_fadt) */

	ACPI_MEMCPY(&acpi_gbl_FADT, table,
		    ACPI_MIN(length, sizeof(struct acpi_table_fadt)));

	/* Convert the local copy of the FADT to the common internal format */

	acpi_tb_convert_fadt();

	/* Validate FADT values now, before we make any changes */

	acpi_tb_validate_fadt();

	/* Initialize the global ACPI register structures */

	acpi_tb_setup_fadt_registers();
}