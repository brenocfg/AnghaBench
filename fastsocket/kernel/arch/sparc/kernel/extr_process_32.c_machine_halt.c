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
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  prom_halt () ; 

void machine_halt(void)
{
	local_irq_enable();
	mdelay(8);
	local_irq_disable();
	prom_halt();
	panic("Halt failed!");
}