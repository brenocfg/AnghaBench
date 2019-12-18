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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct thread_info {int dummy; } ;
struct task_struct {int dummy; } ;
struct pt_regs {scalar_t__ cp0_epc; scalar_t__ cp0_cause; scalar_t__ cp0_badvaddr; scalar_t__ hi; scalar_t__ lo; scalar_t__ cp0_status; scalar_t__* regs; } ;

/* Variables and functions */
 unsigned long THREAD_SIZE ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
	int reg;
	struct thread_info *ti = task_thread_info(p);
	unsigned long ksp = (unsigned long)ti + THREAD_SIZE - 32;
	struct pt_regs *regs = (struct pt_regs *)ksp - 1;
#if (KGDB_GDB_REG_SIZE == 32)
	u32 *ptr = (u32 *)gdb_regs;
#else
	u64 *ptr = (u64 *)gdb_regs;
#endif

	for (reg = 0; reg < 16; reg++)
		*(ptr++) = regs->regs[reg];

	/* S0 - S7 */
	for (reg = 16; reg < 24; reg++)
		*(ptr++) = regs->regs[reg];

	for (reg = 24; reg < 28; reg++)
		*(ptr++) = 0;

	/* GP, SP, FP, RA */
	for (reg = 28; reg < 32; reg++)
		*(ptr++) = regs->regs[reg];

	*(ptr++) = regs->cp0_status;
	*(ptr++) = regs->lo;
	*(ptr++) = regs->hi;
	*(ptr++) = regs->cp0_badvaddr;
	*(ptr++) = regs->cp0_cause;
	*(ptr++) = regs->cp0_epc;
}