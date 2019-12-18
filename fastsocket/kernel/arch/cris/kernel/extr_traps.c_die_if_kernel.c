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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_BUG (struct pt_regs*) ; 
 scalar_t__ oops_in_progress ; 
 int /*<<< orphan*/  printk (char*,char const*,long) ; 
 int /*<<< orphan*/  reset_watchdog () ; 
 int /*<<< orphan*/  show_registers (struct pt_regs*) ; 
 int /*<<< orphan*/  stop_watchdog () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void
die_if_kernel(const char *str, struct pt_regs *regs, long err)
{
	if (user_mode(regs))
		return;

#ifdef CONFIG_ETRAX_WATCHDOG_NICE_DOGGY
	/*
	 * This printout might take too long and could trigger
	 * the watchdog normally. If NICE_DOGGY is set, simply
	 * stop the watchdog during the printout.
	 */
	stop_watchdog();
#endif

	handle_BUG(regs);

	printk("%s: %04lx\n", str, err & 0xffff);

	show_registers(regs);

	oops_in_progress = 0;

#ifdef CONFIG_ETRAX_WATCHDOG_NICE_DOGGY
	reset_watchdog();
#endif
	do_exit(SIGSEGV);
}