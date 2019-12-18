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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 TYPE_1__* of_console_device ; 
 int /*<<< orphan*/  prom_halt () ; 
 int /*<<< orphan*/  prom_halt_power_off () ; 
 scalar_t__ scons_pwroff ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void machine_power_off(void)
{
	if (strcmp(of_console_device->type, "serial") || scons_pwroff)
		prom_halt_power_off();

	prom_halt();
}