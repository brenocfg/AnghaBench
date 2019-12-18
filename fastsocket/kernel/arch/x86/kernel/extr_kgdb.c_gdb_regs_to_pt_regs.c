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
typedef  void* u32 ;
struct pt_regs {unsigned long ax; unsigned long bx; unsigned long cx; unsigned long dx; unsigned long si; unsigned long di; unsigned long bp; unsigned long ip; unsigned long flags; unsigned long ds; unsigned long es; unsigned long cs; unsigned long r8; unsigned long r9; unsigned long r10; unsigned long r11; unsigned long r12; unsigned long r13; unsigned long r14; unsigned long r15; void* ss; } ;

/* Variables and functions */
 size_t GDB_AX ; 
 size_t GDB_BP ; 
 size_t GDB_BX ; 
 size_t GDB_CS ; 
 size_t GDB_CX ; 
 size_t GDB_DI ; 
 size_t GDB_DS ; 
 size_t GDB_DX ; 
 size_t GDB_ES ; 
 size_t GDB_PC ; 
 size_t GDB_PS ; 
 size_t GDB_R10 ; 
 size_t GDB_R11 ; 
 size_t GDB_R12 ; 
 size_t GDB_R13 ; 
 size_t GDB_R14 ; 
 size_t GDB_R15 ; 
 size_t GDB_R8 ; 
 size_t GDB_R9 ; 
 size_t GDB_SI ; 
 size_t GDB_SS ; 

void gdb_regs_to_pt_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
#ifndef CONFIG_X86_32
	u32 *gdb_regs32 = (u32 *)gdb_regs;
#endif
	regs->ax		= gdb_regs[GDB_AX];
	regs->bx		= gdb_regs[GDB_BX];
	regs->cx		= gdb_regs[GDB_CX];
	regs->dx		= gdb_regs[GDB_DX];
	regs->si		= gdb_regs[GDB_SI];
	regs->di		= gdb_regs[GDB_DI];
	regs->bp		= gdb_regs[GDB_BP];
	regs->ip		= gdb_regs[GDB_PC];
#ifdef CONFIG_X86_32
	regs->flags		= gdb_regs[GDB_PS];
	regs->ds		= gdb_regs[GDB_DS];
	regs->es		= gdb_regs[GDB_ES];
	regs->cs		= gdb_regs[GDB_CS];
#else
	regs->r8		= gdb_regs[GDB_R8];
	regs->r9		= gdb_regs[GDB_R9];
	regs->r10		= gdb_regs[GDB_R10];
	regs->r11		= gdb_regs[GDB_R11];
	regs->r12		= gdb_regs[GDB_R12];
	regs->r13		= gdb_regs[GDB_R13];
	regs->r14		= gdb_regs[GDB_R14];
	regs->r15		= gdb_regs[GDB_R15];
	regs->flags		= gdb_regs32[GDB_PS];
	regs->cs		= gdb_regs32[GDB_CS];
	regs->ss		= gdb_regs32[GDB_SS];
#endif
}