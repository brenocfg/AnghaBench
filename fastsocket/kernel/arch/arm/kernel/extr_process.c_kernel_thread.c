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
struct pt_regs {unsigned long ARM_r1; unsigned long ARM_r2; unsigned long ARM_r3; unsigned long ARM_pc; int ARM_cpsr; } ;
typedef  int /*<<< orphan*/  regs ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 unsigned long CLONE_UNTRACED ; 
 unsigned long CLONE_VM ; 
 int PSR_ENDSTATE ; 
 int PSR_ISETSTATE ; 
 int SVC_MODE ; 
 int /*<<< orphan*/  do_fork (unsigned long,int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kernel_thread_exit ; 
 scalar_t__ kernel_thread_helper ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 

pid_t kernel_thread(int (*fn)(void *), void *arg, unsigned long flags)
{
	struct pt_regs regs;

	memset(&regs, 0, sizeof(regs));

	regs.ARM_r1 = (unsigned long)arg;
	regs.ARM_r2 = (unsigned long)fn;
	regs.ARM_r3 = (unsigned long)kernel_thread_exit;
	regs.ARM_pc = (unsigned long)kernel_thread_helper;
	regs.ARM_cpsr = SVC_MODE | PSR_ENDSTATE | PSR_ISETSTATE;

	return do_fork(flags|CLONE_VM|CLONE_UNTRACED, 0, &regs, 0, NULL, NULL);
}