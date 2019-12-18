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
struct TYPE_3__ {unsigned long value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  member_0; } ;
struct acpi_video_bus {TYPE_2__* device; } ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int AE_OK ; 
 int EINVAL ; 
 int acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 

__attribute__((used)) static int
acpi_video_bus_set_POST(struct acpi_video_bus *video, unsigned long option)
{
	int status;
	unsigned long long tmp;
	union acpi_object arg0 = { ACPI_TYPE_INTEGER };
	struct acpi_object_list args = { 1, &arg0 };


	arg0.integer.value = option;

	status = acpi_evaluate_integer(video->device->handle, "_SPD", &args, &tmp);
	if (ACPI_SUCCESS(status))
		status = tmp ? (-EINVAL) : (AE_OK);

	return status;
}