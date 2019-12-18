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
struct TYPE_2__ {int /*<<< orphan*/  version; int /*<<< orphan*/ * gregs; } ;
struct ucontext {TYPE_1__ uc_mcontext; } ;
struct switch_stack {int /*<<< orphan*/  a6; int /*<<< orphan*/  a5; int /*<<< orphan*/  a4; int /*<<< orphan*/  a3; int /*<<< orphan*/  d7; int /*<<< orphan*/  d6; } ;
struct pt_regs {int /*<<< orphan*/  sr; int /*<<< orphan*/  pc; int /*<<< orphan*/  a2; int /*<<< orphan*/  a1; int /*<<< orphan*/  a0; int /*<<< orphan*/  d5; int /*<<< orphan*/  d4; int /*<<< orphan*/  d3; int /*<<< orphan*/  d2; int /*<<< orphan*/  d1; int /*<<< orphan*/  d0; } ;
typedef  int /*<<< orphan*/  greg_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCONTEXT_VERSION ; 
 int __put_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdusp () ; 
 int rt_save_fpu_state (struct ucontext*,struct pt_regs*) ; 

__attribute__((used)) static inline int rt_setup_ucontext(struct ucontext *uc, struct pt_regs *regs)
{
	struct switch_stack *sw = (struct switch_stack *)regs - 1;
	greg_t *gregs = uc->uc_mcontext.gregs;
	int err = 0;

	err |= __put_user(MCONTEXT_VERSION, &uc->uc_mcontext.version);
	err |= __put_user(regs->d0, &gregs[0]);
	err |= __put_user(regs->d1, &gregs[1]);
	err |= __put_user(regs->d2, &gregs[2]);
	err |= __put_user(regs->d3, &gregs[3]);
	err |= __put_user(regs->d4, &gregs[4]);
	err |= __put_user(regs->d5, &gregs[5]);
	err |= __put_user(sw->d6, &gregs[6]);
	err |= __put_user(sw->d7, &gregs[7]);
	err |= __put_user(regs->a0, &gregs[8]);
	err |= __put_user(regs->a1, &gregs[9]);
	err |= __put_user(regs->a2, &gregs[10]);
	err |= __put_user(sw->a3, &gregs[11]);
	err |= __put_user(sw->a4, &gregs[12]);
	err |= __put_user(sw->a5, &gregs[13]);
	err |= __put_user(sw->a6, &gregs[14]);
	err |= __put_user(rdusp(), &gregs[15]);
	err |= __put_user(regs->pc, &gregs[16]);
	err |= __put_user(regs->sr, &gregs[17]);
#ifdef CONFIG_FPU
	err |= rt_save_fpu_state(uc, regs);
#endif
	return err;
}