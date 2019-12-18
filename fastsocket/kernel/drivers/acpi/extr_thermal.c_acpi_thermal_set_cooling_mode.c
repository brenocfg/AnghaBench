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
struct TYPE_3__ {int value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  member_0; } ;
struct acpi_thermal {TYPE_2__* device; } ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/ * acpi_handle ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_OK ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int acpi_thermal_set_cooling_mode(struct acpi_thermal *tz, int mode)
{
	acpi_status status = AE_OK;
	union acpi_object arg0 = { ACPI_TYPE_INTEGER };
	struct acpi_object_list arg_list = { 1, &arg0 };
	acpi_handle handle = NULL;


	if (!tz)
		return -EINVAL;

	status = acpi_get_handle(tz->device->handle, "_SCP", &handle);
	if (ACPI_FAILURE(status)) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "_SCP not present\n"));
		return -ENODEV;
	}

	arg0.integer.value = mode;

	status = acpi_evaluate_object(handle, NULL, &arg_list, NULL);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	return 0;
}