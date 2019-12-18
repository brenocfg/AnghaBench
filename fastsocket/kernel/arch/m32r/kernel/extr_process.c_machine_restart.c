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

/* Variables and functions */
 scalar_t__ PLD_REBOOT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  outw (int,unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 

void machine_restart(char *__unused)
{
#if defined(CONFIG_PLAT_MAPPI3)
	outw(1, (unsigned long)PLD_REBOOT);
#endif

	printk("Please push reset button!\n");
	while (1)
		cpu_relax();
}