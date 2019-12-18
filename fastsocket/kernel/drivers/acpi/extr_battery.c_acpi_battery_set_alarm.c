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
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
struct acpi_battery {int /*<<< orphan*/  alarm; int /*<<< orphan*/  lock; TYPE_2__* device; int /*<<< orphan*/  alarm_present; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_battery_present (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_battery_set_alarm(struct acpi_battery *battery)
{
	acpi_status status = 0;
	union acpi_object arg0 = { .type = ACPI_TYPE_INTEGER };
	struct acpi_object_list arg_list = { 1, &arg0 };

	if (!acpi_battery_present(battery)|| !battery->alarm_present)
		return -ENODEV;

	arg0.integer.value = battery->alarm;

	mutex_lock(&battery->lock);
	status = acpi_evaluate_object(battery->device->handle, "_BTP",
				 &arg_list, NULL);
	mutex_unlock(&battery->lock);

	if (ACPI_FAILURE(status))
		return -ENODEV;

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Alarm set to %d\n", battery->alarm));
	return 0;
}