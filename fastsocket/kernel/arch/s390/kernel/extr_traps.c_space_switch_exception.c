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
struct TYPE_2__ {int mask; } ;
struct pt_regs {TYPE_1__ psw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILL_PRVOPC ; 
 int PSW_ASC_HOME ; 
 int PSW_MASK_PSTATE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  do_trap (struct pt_regs*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void space_switch_exception(struct pt_regs * regs, long int_code)
{
	/* Set user psw back to home space mode. */
	if (regs->psw.mask & PSW_MASK_PSTATE)
		regs->psw.mask |= PSW_ASC_HOME;
	/* Send SIGILL. */
	do_trap(regs, int_code, SIGILL, ILL_PRVOPC, "space switch event");
}