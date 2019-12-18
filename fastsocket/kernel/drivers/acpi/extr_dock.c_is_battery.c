#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
struct acpi_device_info {int valid; TYPE_1__ hardware_id; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ACPI_VALID_HID ; 
 int /*<<< orphan*/  acpi_get_object_info (int /*<<< orphan*/ ,struct acpi_device_info**) ; 
 int /*<<< orphan*/  kfree (struct acpi_device_info*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_battery(acpi_handle handle)
{
	struct acpi_device_info *info;
	int ret = 1;

	if (!ACPI_SUCCESS(acpi_get_object_info(handle, &info)))
		return 0;
	if (!(info->valid & ACPI_VALID_HID))
		ret = 0;
	else
		ret = !strcmp("PNP0C0A", info->hardware_id.string);

	kfree(info);
	return ret;
}