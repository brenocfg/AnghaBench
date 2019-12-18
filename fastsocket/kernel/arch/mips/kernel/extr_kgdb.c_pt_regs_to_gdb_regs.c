#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int cp0_status; int /*<<< orphan*/  cp0_epc; int /*<<< orphan*/  cp0_cause; int /*<<< orphan*/  cp0_badvaddr; int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; int /*<<< orphan*/ * regs; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fpr; } ;
struct TYPE_6__ {TYPE_1__ fpu; } ;
struct TYPE_7__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int ST0_CU1 ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  save_fp (TYPE_3__*) ; 

void pt_regs_to_gdb_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	int reg;

#if (KGDB_GDB_REG_SIZE == 32)
	u32 *ptr = (u32 *)gdb_regs;
#else
	u64 *ptr = (u64 *)gdb_regs;
#endif

	for (reg = 0; reg < 32; reg++)
		*(ptr++) = regs->regs[reg];

	*(ptr++) = regs->cp0_status;
	*(ptr++) = regs->lo;
	*(ptr++) = regs->hi;
	*(ptr++) = regs->cp0_badvaddr;
	*(ptr++) = regs->cp0_cause;
	*(ptr++) = regs->cp0_epc;

	/* FP REGS */
	if (!(current && (regs->cp0_status & ST0_CU1)))
		return;

	save_fp(current);
	for (reg = 0; reg < 32; reg++)
		*(ptr++) = current->thread.fpu.fpr[reg];
}