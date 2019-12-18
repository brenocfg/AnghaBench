#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ present; } ;
struct TYPE_6__ {TYPE_1__ status; } ;
struct TYPE_5__ {TYPE_3__* device; } ;

/* Variables and functions */
 int EINVAL ; 
 int acpi_bus_get_status (TYPE_3__*) ; 
 int asus_hotk_get_info () ; 
 TYPE_2__* hotk ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int asus_hotk_check(void)
{
	int result = 0;

	result = acpi_bus_get_status(hotk->device);
	if (result)
		return result;

	if (hotk->device->status.present) {
		result = asus_hotk_get_info();
	} else {
		pr_err("Hotkey device not present, aborting\n");
		return -EINVAL;
	}

	return result;
}