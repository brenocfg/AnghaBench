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
struct pt_regs {int /*<<< orphan*/ * gpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FULL_REGS (struct pt_regs*) ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int do_fork (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int sys_fork(unsigned long p1, unsigned long p2, unsigned long p3,
	     unsigned long p4, unsigned long p5, unsigned long p6,
	     struct pt_regs *regs)
{
	CHECK_FULL_REGS(regs);
	return do_fork(SIGCHLD, regs->gpr[1], regs, 0, NULL, NULL);
}