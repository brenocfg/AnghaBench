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
typedef  int u_short ;
typedef  scalar_t__ u_char ;

/* Variables and functions */
 size_t CyCCR ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  my_udelay (long) ; 

u_short write_cy_cmd(volatile u_char * base_addr, u_char cmd)
{
	unsigned long flags;
	volatile int i;

	local_irq_save(flags);
	/* Check to see that the previous command has completed */
	for (i = 0; i < 100; i++) {
		if (base_addr[CyCCR] == 0) {
			break;
		}
		my_udelay(10L);
	}
	/* if the CCR never cleared, the previous command
	   didn't finish within the "reasonable time" */
	if (i == 10) {
		local_irq_restore(flags);
		return (-1);
	}

	/* Issue the new command */
	base_addr[CyCCR] = cmd;
	local_irq_restore(flags);
	return (0);
}