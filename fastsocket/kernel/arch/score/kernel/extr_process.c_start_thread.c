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
struct pt_regs {unsigned long cp0_psr; unsigned long cp0_epc; unsigned long* regs; } ;

/* Variables and functions */
 unsigned long KU_MASK ; 
 unsigned long KU_USER ; 

void start_thread(struct pt_regs *regs, unsigned long pc, unsigned long sp)
{
	unsigned long status;

	/* New thread loses kernel privileges. */
	status = regs->cp0_psr & ~(KU_MASK);
	status |= KU_USER;
	regs->cp0_psr = status;
	regs->cp0_epc = pc;
	regs->regs[0] = sp;
}