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
struct acpi_sbs {int dummy; } ;
struct acpi_device {struct acpi_sbs* driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  acpi_sbs_callback (struct acpi_sbs*) ; 

__attribute__((used)) static int acpi_sbs_resume(struct acpi_device *device)
{
	struct acpi_sbs *sbs;
	if (!device)
		return -EINVAL;
	sbs = device->driver_data;
	acpi_sbs_callback(sbs);
	return 0;
}