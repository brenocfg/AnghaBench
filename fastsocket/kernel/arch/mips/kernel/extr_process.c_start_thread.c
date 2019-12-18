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
struct pt_regs {unsigned long cp0_status; unsigned long cp0_epc; unsigned long* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr_limit; } ;

/* Variables and functions */
 unsigned long KU_MASK ; 
 unsigned long KU_USER ; 
 unsigned long ST0_CU0 ; 
 unsigned long ST0_CU1 ; 
 unsigned long ST0_FR ; 
 int /*<<< orphan*/  TIF_32BIT_REGS ; 
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  __init_dsp () ; 
 int /*<<< orphan*/  clear_fpu_owner () ; 
 int /*<<< orphan*/  clear_used_math () ; 
 scalar_t__ cpu_has_dsp ; 
 TYPE_1__* current_thread_info () ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

void start_thread(struct pt_regs * regs, unsigned long pc, unsigned long sp)
{
	unsigned long status;

	/* New thread loses kernel privileges. */
	status = regs->cp0_status & ~(ST0_CU0|ST0_CU1|ST0_FR|KU_MASK);
#ifdef CONFIG_64BIT
	status |= test_thread_flag(TIF_32BIT_REGS) ? 0 : ST0_FR;
#endif
	status |= KU_USER;
	regs->cp0_status = status;
	clear_used_math();
	clear_fpu_owner();
	if (cpu_has_dsp)
		__init_dsp();
	regs->cp0_epc = pc;
	regs->regs[29] = sp;
	current_thread_info()->addr_limit = USER_DS;
}