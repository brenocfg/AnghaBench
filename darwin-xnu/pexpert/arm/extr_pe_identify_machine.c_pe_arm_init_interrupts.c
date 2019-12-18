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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,void*) ; 
 int /*<<< orphan*/  pe_arm_init_timer (void*) ; 
 int /*<<< orphan*/  pe_arm_map_interrupt_controller () ; 

uint32_t
pe_arm_init_interrupts(void *args)
{
	kprintf("pe_arm_init_interrupts: args: %p\n", args);

	/* Set up mappings for interrupt controller and possibly timers (if they haven't been set up already) */
	if (args != NULL) {
		if (!pe_arm_map_interrupt_controller()) {
			return 0;
		}
	}

	return pe_arm_init_timer(args);
}