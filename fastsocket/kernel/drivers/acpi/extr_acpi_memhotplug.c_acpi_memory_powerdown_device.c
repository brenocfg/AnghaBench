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
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_memory_device {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 unsigned long long ACPI_STA_DEVICE_ENABLED ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_memory_powerdown_device(struct acpi_memory_device *mem_device)
{
	acpi_status status;
	struct acpi_object_list arg_list;
	union acpi_object arg;
	unsigned long long current_status;


	/* Issue the _EJ0 command */
	arg_list.count = 1;
	arg_list.pointer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.integer.value = 1;
	status = acpi_evaluate_object(mem_device->device->handle,
				      "_EJ0", &arg_list, NULL);
	/* Return on _EJ0 failure */
	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "_EJ0 failed"));
		return -ENODEV;
	}

	/* Evalute _STA to check if the device is disabled */
	status = acpi_evaluate_integer(mem_device->device->handle, "_STA",
				       NULL, &current_status);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	/* Check for device status.  Device should be disabled */
	if (current_status & ACPI_STA_DEVICE_ENABLED)
		return -EINVAL;

	return 0;
}