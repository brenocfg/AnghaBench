#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
struct TYPE_6__ {scalar_t__ Xfacs; scalar_t__ Xdsdt; } ;
struct TYPE_5__ {TYPE_1__* tables; } ;
struct TYPE_4__ {size_t length; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  ACPI_SIG_FACS ; 
 int /*<<< orphan*/  ACPI_TABLE_INDEX_DSDT ; 
 int /*<<< orphan*/  ACPI_TABLE_INDEX_FACS ; 
 TYPE_3__ acpi_gbl_FADT ; 
 TYPE_2__ acpi_gbl_root_table_list ; 
 struct acpi_table_header* acpi_os_map_memory (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  acpi_os_unmap_memory (struct acpi_table_header*,size_t) ; 
 int /*<<< orphan*/  acpi_tb_create_local_fadt (struct acpi_table_header*,size_t) ; 
 int /*<<< orphan*/  acpi_tb_install_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_verify_checksum (struct acpi_table_header*,size_t) ; 

void acpi_tb_parse_fadt(u32 table_index)
{
	u32 length;
	struct acpi_table_header *table;

	/*
	 * The FADT has multiple versions with different lengths,
	 * and it contains pointers to both the DSDT and FACS tables.
	 *
	 * Get a local copy of the FADT and convert it to a common format
	 * Map entire FADT, assumed to be smaller than one page.
	 */
	length = acpi_gbl_root_table_list.tables[table_index].length;

	table =
	    acpi_os_map_memory(acpi_gbl_root_table_list.tables[table_index].
			       address, length);
	if (!table) {
		return;
	}

	/*
	 * Validate the FADT checksum before we copy the table. Ignore
	 * checksum error as we want to try to get the DSDT and FACS.
	 */
	(void)acpi_tb_verify_checksum(table, length);

	/* Create a local copy of the FADT in common ACPI 2.0+ format */

	acpi_tb_create_local_fadt(table, length);

	/* All done with the real FADT, unmap it */

	acpi_os_unmap_memory(table, length);

	/* Obtain the DSDT and FACS tables via their addresses within the FADT */

	acpi_tb_install_table((acpi_physical_address) acpi_gbl_FADT.Xdsdt,
			      ACPI_SIG_DSDT, ACPI_TABLE_INDEX_DSDT);

	acpi_tb_install_table((acpi_physical_address) acpi_gbl_FADT.Xfacs,
			      ACPI_SIG_FACS, ACPI_TABLE_INDEX_FACS);
}