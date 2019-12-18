#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpi_device {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  acpi_driver_data (struct acpi_device*) ; 
 TYPE_1__* hotk ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static int asus_hotk_remove(struct acpi_device *device, int type)
{
	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	kfree(hotk->name);
	kfree(hotk);

	return 0;
}