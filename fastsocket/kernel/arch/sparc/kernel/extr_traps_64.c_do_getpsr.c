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
struct pt_regs {int tpc; int tnpc; int /*<<< orphan*/  tstate; int /*<<< orphan*/ * u_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_32BIT ; 
 size_t UREG_I0 ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstate_to_psr (int /*<<< orphan*/ ) ; 

void do_getpsr(struct pt_regs *regs)
{
	regs->u_regs[UREG_I0] = tstate_to_psr(regs->tstate);
	regs->tpc   = regs->tnpc;
	regs->tnpc += 4;
	if (test_thread_flag(TIF_32BIT)) {
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	}
}