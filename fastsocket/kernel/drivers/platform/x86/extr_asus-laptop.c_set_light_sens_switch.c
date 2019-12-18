#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int light_switch; } ;

/* Variables and functions */
 TYPE_1__* hotk ; 
 int /*<<< orphan*/  ls_switch_handle ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_light_sens_switch(int value)
{
	if (write_acpi_int(ls_switch_handle, NULL, value, NULL))
		pr_warning("Error setting light sensor switch\n");
	hotk->light_switch = value;
}