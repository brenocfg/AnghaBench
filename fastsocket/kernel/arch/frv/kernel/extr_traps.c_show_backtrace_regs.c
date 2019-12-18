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
struct pt_regs {int psr; } ;

/* Variables and functions */
 int NR_PT_REGS ; 
 int PSR_S ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/ * regnames ; 

__attribute__((used)) static void show_backtrace_regs(struct pt_regs *frame)
{
	unsigned long *reg;
	int loop;

	/* print the registers for this frame */
	printk("<-- %s Frame: @%p -->\n",
	       frame->psr & PSR_S ? "Kernel Mode" : "User Mode",
	       frame);

	reg = (unsigned long *) frame;
	for (loop = 0; loop < NR_PT_REGS; loop++) {
		printk("%s %08lx", regnames[loop + 0], reg[loop + 0]);

		if (loop == NR_PT_REGS - 1 || loop % 5 == 4)
			printk("\n");
		else
			printk(" | ");
	}

	printk("--------\n");
}