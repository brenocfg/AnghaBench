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
struct acpi_table_header {int dummy; } ;
struct acpi_table_attr {int /*<<< orphan*/  node; int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int AE_OK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int acpi_get_table_by_index (int,struct acpi_table_header**) ; 
 int acpi_install_table_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_kobj ; 
 int /*<<< orphan*/  acpi_sysfs_table_handler ; 
 int /*<<< orphan*/  acpi_table_attr_init (struct acpi_table_attr*,struct acpi_table_header*) ; 
 int /*<<< orphan*/  acpi_table_attr_list ; 
 int /*<<< orphan*/  dynamic_tables_kobj ; 
 int /*<<< orphan*/  kfree (struct acpi_table_attr*) ; 
 int /*<<< orphan*/  kobject_create_and_add (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_table_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tables_kobj ; 

__attribute__((used)) static int acpi_system_sysfs_init(void)
{
	struct acpi_table_attr *table_attr;
	struct acpi_table_header *table_header = NULL;
	int table_index = 0;
	int result;

	tables_kobj = kobject_create_and_add("tables", acpi_kobj);
	if (!tables_kobj)
		goto err;

	dynamic_tables_kobj = kobject_create_and_add("dynamic", tables_kobj);
	if (!dynamic_tables_kobj)
		goto err_dynamic_tables;

	do {
		result = acpi_get_table_by_index(table_index, &table_header);
		if (!result) {
			table_index++;
			table_attr = NULL;
			table_attr =
			    kzalloc(sizeof(struct acpi_table_attr), GFP_KERNEL);
			if (!table_attr)
				return -ENOMEM;

			acpi_table_attr_init(table_attr, table_header);
			result =
			    sysfs_create_bin_file(tables_kobj,
						  &table_attr->attr);
			if (result) {
				kfree(table_attr);
				return result;
			} else
				list_add_tail(&table_attr->node,
					      &acpi_table_attr_list);
		}
	} while (!result);
	kobject_uevent(tables_kobj, KOBJ_ADD);
	kobject_uevent(dynamic_tables_kobj, KOBJ_ADD);
	result = acpi_install_table_handler(acpi_sysfs_table_handler, NULL);

	return result == AE_OK ? 0 : -EINVAL;
err_dynamic_tables:
	kobject_put(tables_kobj);
err:
	return -ENOMEM;
}