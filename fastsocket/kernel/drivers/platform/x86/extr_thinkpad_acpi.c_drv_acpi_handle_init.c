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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPACPI_DBG_INIT ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dbg_printk (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void drv_acpi_handle_init(char *name,
			   acpi_handle *handle, acpi_handle parent,
			   char **paths, int num_paths, char **path)
{
	int i;
	acpi_status status;

	vdbg_printk(TPACPI_DBG_INIT, "trying to locate ACPI handle for %s\n",
		name);

	for (i = 0; i < num_paths; i++) {
		status = acpi_get_handle(parent, paths[i], handle);
		if (ACPI_SUCCESS(status)) {
			*path = paths[i];
			dbg_printk(TPACPI_DBG_INIT,
				   "Found ACPI handle %s for %s\n",
				   *path, name);
			return;
		}
	}

	vdbg_printk(TPACPI_DBG_INIT, "ACPI handle for %s not found\n",
		    name);
	*handle = NULL;
}