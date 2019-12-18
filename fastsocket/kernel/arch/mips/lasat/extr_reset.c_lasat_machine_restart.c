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
struct TYPE_2__ {int* reset_reg; } ;

/* Variables and functions */
 scalar_t__ lasat_boot_to_service ; 
 TYPE_1__* lasat_misc ; 
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static void lasat_machine_restart(char *command)
{
	local_irq_disable();

	if (lasat_boot_to_service) {
		*(volatile unsigned int *)0xa0000024 = 0xdeadbeef;
		*(volatile unsigned int *)0xa00000fc = 0xfedeabba;
	}
	*lasat_misc->reset_reg = 0xbedead;
	for (;;) ;
}