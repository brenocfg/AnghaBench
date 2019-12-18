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
struct task_struct {int dummy; } ;
struct pt_regs {unsigned long ARM_r0; unsigned long ARM_r1; unsigned long ARM_r2; unsigned long ARM_r3; unsigned long ARM_r4; unsigned long ARM_r5; unsigned long ARM_r6; unsigned long ARM_r7; unsigned long ARM_r8; unsigned long ARM_r9; unsigned long ARM_r10; unsigned long ARM_fp; unsigned long ARM_ip; unsigned long ARM_sp; unsigned long ARM_lr; unsigned long ARM_pc; unsigned long ARM_cpsr; } ;

/* Variables and functions */
 int GDB_MAX_REGS ; 
 size_t _CPSR ; 
 size_t _FP ; 
 size_t _IP ; 
 size_t _LR ; 
 size_t _PC ; 
 size_t _R0 ; 
 size_t _R1 ; 
 size_t _R10 ; 
 size_t _R2 ; 
 size_t _R3 ; 
 size_t _R4 ; 
 size_t _R5 ; 
 size_t _R6 ; 
 size_t _R7 ; 
 size_t _R8 ; 
 size_t _R9 ; 
 size_t _SPT ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

void
sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *task)
{
	struct pt_regs *thread_regs;
	int regno;

	/* Just making sure... */
	if (task == NULL)
		return;

	/* Initialize to zero */
	for (regno = 0; regno < GDB_MAX_REGS; regno++)
		gdb_regs[regno] = 0;

	/* Otherwise, we have only some registers from switch_to() */
	thread_regs		= task_pt_regs(task);
	gdb_regs[_R0]		= thread_regs->ARM_r0;
	gdb_regs[_R1]		= thread_regs->ARM_r1;
	gdb_regs[_R2]		= thread_regs->ARM_r2;
	gdb_regs[_R3]		= thread_regs->ARM_r3;
	gdb_regs[_R4]		= thread_regs->ARM_r4;
	gdb_regs[_R5]		= thread_regs->ARM_r5;
	gdb_regs[_R6]		= thread_regs->ARM_r6;
	gdb_regs[_R7]		= thread_regs->ARM_r7;
	gdb_regs[_R8]		= thread_regs->ARM_r8;
	gdb_regs[_R9]		= thread_regs->ARM_r9;
	gdb_regs[_R10]		= thread_regs->ARM_r10;
	gdb_regs[_FP]		= thread_regs->ARM_fp;
	gdb_regs[_IP]		= thread_regs->ARM_ip;
	gdb_regs[_SPT]		= thread_regs->ARM_sp;
	gdb_regs[_LR]		= thread_regs->ARM_lr;
	gdb_regs[_PC]		= thread_regs->ARM_pc;
	gdb_regs[_CPSR]		= thread_regs->ARM_cpsr;
}