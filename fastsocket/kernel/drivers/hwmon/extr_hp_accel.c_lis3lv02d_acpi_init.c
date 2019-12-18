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
struct lis3lv02d {struct acpi_device* bus_priv; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ AE_OK ; 
 int EINVAL ; 
 int /*<<< orphan*/  METHOD_NAME__INI ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int lis3lv02d_acpi_init(struct lis3lv02d *lis3)
{
	struct acpi_device *dev = lis3->bus_priv;
	if (acpi_evaluate_object(dev->handle, METHOD_NAME__INI,
				 NULL, NULL) != AE_OK)
		return -EINVAL;

	return 0;
}