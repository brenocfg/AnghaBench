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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int sprintf (char*,char*,unsigned long long) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static ssize_t
acpi_device_sun_show(struct device *dev, struct device_attribute *attr,
		     char *buf) {
	struct acpi_device *acpi_dev = to_acpi_device(dev);
	unsigned long long sun;
	int result;

	result = acpi_evaluate_integer(acpi_dev->handle, "_SUN", NULL, &sun);
	if (result)
		goto end;

	result = sprintf(buf, "%llu\n", sun);
end:
	return result;
}