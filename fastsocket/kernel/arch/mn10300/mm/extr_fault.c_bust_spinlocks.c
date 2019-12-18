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
 int console_loglevel ; 
 scalar_t__ global_irq_lock ; 
 int oops_in_progress ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  unblank_screen () ; 

void bust_spinlocks(int yes)
{
	if (yes) {
		oops_in_progress = 1;
#ifdef CONFIG_SMP
		/* Many serial drivers do __global_cli() */
		global_irq_lock = 0;
#endif
	} else {
		int loglevel_save = console_loglevel;
#ifdef CONFIG_VT
		unblank_screen();
#endif
		oops_in_progress = 0;
		/*
		 * OK, the message is on the console.  Now we call printk()
		 * without oops_in_progress set so that printk will give klogd
		 * a poke.  Hold onto your hats...
		 */
		console_loglevel = 15;	/* NMI oopser may have shut the console
					 * up */
		printk(" ");
		console_loglevel = loglevel_save;
	}
}