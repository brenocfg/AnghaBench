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
struct acpi_table_attr {int /*<<< orphan*/  node; int /*<<< orphan*/  attr; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
#define  ACPI_TABLE_EVENT_LOAD 129 
#define  ACPI_TABLE_EVENT_UNLOAD 128 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_table_attr_init (struct acpi_table_attr*,void*) ; 
 int /*<<< orphan*/  acpi_table_attr_list ; 
 int /*<<< orphan*/  dynamic_tables_kobj ; 
 int /*<<< orphan*/  kfree (struct acpi_table_attr*) ; 
 struct acpi_table_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_create_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
acpi_sysfs_table_handler(u32 event, void *table, void *context)
{
	struct acpi_table_attr *table_attr;

	switch (event) {
	case ACPI_TABLE_EVENT_LOAD:
		table_attr =
			kzalloc(sizeof(struct acpi_table_attr), GFP_KERNEL);
		if (!table_attr)
			return AE_NO_MEMORY;

		acpi_table_attr_init(table_attr, table);
		if (sysfs_create_bin_file(dynamic_tables_kobj,
					&table_attr->attr)) {
			kfree(table_attr);
			return AE_ERROR;
		} else
			list_add_tail(&table_attr->node,
					&acpi_table_attr_list);
		break;
	case ACPI_TABLE_EVENT_UNLOAD:
		/*
		 * we do not need to do anything right now
		 * because the table is not deleted from the
		 * global table list when unloading it.
		 */
		break;
	default:
		return AE_BAD_PARAMETER;
	}
	return AE_OK;
}