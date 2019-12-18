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
struct acpi_table_desc {int flags; int /*<<< orphan*/ * pointer; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ *) ; 
#define  ACPI_TABLE_ORIGIN_ALLOCATED 129 
#define  ACPI_TABLE_ORIGIN_MAPPED 128 
 int ACPI_TABLE_ORIGIN_MASK ; 
 int /*<<< orphan*/  acpi_os_unmap_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void acpi_tb_delete_table(struct acpi_table_desc *table_desc)
{
	/* Table must be mapped or allocated */
	if (!table_desc->pointer) {
		return;
	}
	switch (table_desc->flags & ACPI_TABLE_ORIGIN_MASK) {
	case ACPI_TABLE_ORIGIN_MAPPED:
		acpi_os_unmap_memory(table_desc->pointer, table_desc->length);
		break;
	case ACPI_TABLE_ORIGIN_ALLOCATED:
		ACPI_FREE(table_desc->pointer);
		break;
	default:;
	}

	table_desc->pointer = NULL;
}