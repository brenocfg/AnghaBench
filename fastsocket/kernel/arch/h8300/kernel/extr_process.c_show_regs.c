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
struct pt_regs {int /*<<< orphan*/  er6; int /*<<< orphan*/  er5; int /*<<< orphan*/  er4; int /*<<< orphan*/  er3; int /*<<< orphan*/  er2; int /*<<< orphan*/  er1; int /*<<< orphan*/  er0; int /*<<< orphan*/  orig_er0; int /*<<< orphan*/  ccr; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  rdusp () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void show_regs(struct pt_regs * regs)
{
	printk("\nPC: %08lx  Status: %02x",
	       regs->pc, regs->ccr);
	printk("\nORIG_ER0: %08lx ER0: %08lx ER1: %08lx",
	       regs->orig_er0, regs->er0, regs->er1);
	printk("\nER2: %08lx ER3: %08lx ER4: %08lx ER5: %08lx",
	       regs->er2, regs->er3, regs->er4, regs->er5);
	printk("\nER6' %08lx ",regs->er6);
	if (user_mode(regs))
		printk("USP: %08lx\n", rdusp());
	else
		printk("\n");
}