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
struct uml_pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_IRQ ; 
 int /*<<< orphan*/  do_IRQ (int /*<<< orphan*/ ,struct uml_pt_regs*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void timer_handler(int sig, struct uml_pt_regs *regs)
{
	unsigned long flags;

	local_irq_save(flags);
	do_IRQ(TIMER_IRQ, regs);
	local_irq_restore(flags);
}