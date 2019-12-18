#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  s390_fp_regs ;
struct TYPE_3__ {int /*<<< orphan*/  fp_regs; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  save_fp_regs (int /*<<< orphan*/ *) ; 

int dump_fpu (struct pt_regs * regs, s390_fp_regs *fpregs)
{
#ifndef CONFIG_64BIT
	/*
	 * save fprs to current->thread.fp_regs to merge them with
	 * the emulated registers and then copy the result to the dump.
	 */
	save_fp_regs(&current->thread.fp_regs);
	memcpy(fpregs, &current->thread.fp_regs, sizeof(s390_fp_regs));
#else /* CONFIG_64BIT */
	save_fp_regs(fpregs);
#endif /* CONFIG_64BIT */
	return 1;
}