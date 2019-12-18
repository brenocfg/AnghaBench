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
struct device {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_free_ids (struct acpi_device*) ; 
 int /*<<< orphan*/  kfree (struct acpi_device*) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static void acpi_device_release(struct device *dev)
{
	struct acpi_device *acpi_dev = to_acpi_device(dev);

	acpi_free_ids(acpi_dev);
	kfree(acpi_dev);
}