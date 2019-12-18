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
 int /*<<< orphan*/  bfin_reset () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  native_machine_restart (char*) ; 
 int /*<<< orphan*/  smp_call_function (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ smp_processor_id () ; 

void machine_restart(char *cmd)
{
	native_machine_restart(cmd);
	local_irq_disable();
	if (smp_processor_id())
		smp_call_function((void *)bfin_reset, 0, 1);
	else
		bfin_reset();
}