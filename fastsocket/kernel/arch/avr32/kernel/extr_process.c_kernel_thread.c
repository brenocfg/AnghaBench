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
struct pt_regs {unsigned long r0; unsigned long r1; unsigned long r2; unsigned long lr; unsigned long pc; int /*<<< orphan*/  sr; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 unsigned long CLONE_UNTRACED ; 
 unsigned long CLONE_VM ; 
 int /*<<< orphan*/  MODE_SUPERVISOR ; 
 scalar_t__ do_exit ; 
 int do_fork (unsigned long,int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kernel_thread_helper ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 

int kernel_thread(int (*fn)(void *), void *arg, unsigned long flags)
{
	struct pt_regs regs;

	memset(&regs, 0, sizeof(regs));

	regs.r0 = (unsigned long)arg;
	regs.r1 = (unsigned long)fn;
	regs.r2 = (unsigned long)do_exit;
	regs.lr = (unsigned long)kernel_thread_helper;
	regs.pc = (unsigned long)kernel_thread_helper;
	regs.sr = MODE_SUPERVISOR;

	return do_fork(flags | CLONE_VM | CLONE_UNTRACED,
		       0, &regs, 0, NULL, NULL);
}