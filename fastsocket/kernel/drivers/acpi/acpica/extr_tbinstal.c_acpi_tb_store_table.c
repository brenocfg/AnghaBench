#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct acpi_table_header {int /*<<< orphan*/  signature; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
struct TYPE_4__ {size_t count; size_t size; TYPE_1__* tables; } ;
struct TYPE_3__ {size_t length; int /*<<< orphan*/  signature; int /*<<< orphan*/  flags; scalar_t__ owner_id; struct acpi_table_header* pointer; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_2__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_tb_resize_root_table_list () ; 

acpi_status
acpi_tb_store_table(acpi_physical_address address,
		    struct acpi_table_header *table,
		    u32 length, u8 flags, u32 *table_index)
{
	acpi_status status = AE_OK;

	/* Ensure that there is room for the table in the Root Table List */

	if (acpi_gbl_root_table_list.count >= acpi_gbl_root_table_list.size) {
		status = acpi_tb_resize_root_table_list();
		if (ACPI_FAILURE(status)) {
			return (status);
		}
	}

	/* Initialize added table */

	acpi_gbl_root_table_list.tables[acpi_gbl_root_table_list.count].
	    address = address;
	acpi_gbl_root_table_list.tables[acpi_gbl_root_table_list.count].
	    pointer = table;
	acpi_gbl_root_table_list.tables[acpi_gbl_root_table_list.count].length =
	    length;
	acpi_gbl_root_table_list.tables[acpi_gbl_root_table_list.count].
	    owner_id = 0;
	acpi_gbl_root_table_list.tables[acpi_gbl_root_table_list.count].flags =
	    flags;

	ACPI_MOVE_32_TO_32(&
			   (acpi_gbl_root_table_list.
			    tables[acpi_gbl_root_table_list.count].signature),
			   table->signature);

	*table_index = acpi_gbl_root_table_list.count;
	acpi_gbl_root_table_list.count++;
	return (status);
}