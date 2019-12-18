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
 scalar_t__ MIPS_BE_DISCARD ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  count_be_interrupt ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ debug_be_interrupt ; 
 int /*<<< orphan*/  die_if_kernel (char*,struct pt_regs const*) ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pt_regs* get_irq_regs () ; 
 scalar_t__ ip28_be_interrupt (struct pt_regs const*) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 

void ip22_be_interrupt(int irq)
{
	const struct pt_regs *regs = get_irq_regs();

	count_be_interrupt++;

	if (ip28_be_interrupt(regs) != MIPS_BE_DISCARD) {
		/* Assume it would be too dangerous to continue ... */
		die_if_kernel("Oops", regs);
		force_sig(SIGBUS, current);
	} else if (debug_be_interrupt)
		show_regs((struct pt_regs *)regs);
}