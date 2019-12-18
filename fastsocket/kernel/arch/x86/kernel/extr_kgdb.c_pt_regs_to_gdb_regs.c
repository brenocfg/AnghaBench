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
typedef  unsigned long u32 ;
struct pt_regs {unsigned long ax; unsigned long bx; unsigned long cx; unsigned long dx; unsigned long si; unsigned long di; unsigned long bp; unsigned long ip; unsigned long flags; unsigned long ds; unsigned long es; unsigned long cs; unsigned long sp; unsigned long r8; unsigned long r9; unsigned long r10; unsigned long r11; unsigned long r12; unsigned long r13; unsigned long r14; unsigned long r15; unsigned long ss; } ;

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
 size_t GDB_FS ; 
 size_t GDB_GS ; 
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
 size_t GDB_SP ; 
 size_t GDB_SS ; 
 unsigned long __KERNEL_DS ; 

void pt_regs_to_gdb_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
#ifndef CONFIG_X86_32
	u32 *gdb_regs32 = (u32 *)gdb_regs;
#endif
	gdb_regs[GDB_AX]	= regs->ax;
	gdb_regs[GDB_BX]	= regs->bx;
	gdb_regs[GDB_CX]	= regs->cx;
	gdb_regs[GDB_DX]	= regs->dx;
	gdb_regs[GDB_SI]	= regs->si;
	gdb_regs[GDB_DI]	= regs->di;
	gdb_regs[GDB_BP]	= regs->bp;
	gdb_regs[GDB_PC]	= regs->ip;
#ifdef CONFIG_X86_32
	gdb_regs[GDB_PS]	= regs->flags;
	gdb_regs[GDB_DS]	= regs->ds;
	gdb_regs[GDB_ES]	= regs->es;
	gdb_regs[GDB_CS]	= regs->cs;
	gdb_regs[GDB_SS]	= __KERNEL_DS;
	gdb_regs[GDB_FS]	= 0xFFFF;
	gdb_regs[GDB_GS]	= 0xFFFF;
	gdb_regs[GDB_SP]	= (int)&regs->sp;
#else
	gdb_regs[GDB_R8]	= regs->r8;
	gdb_regs[GDB_R9]	= regs->r9;
	gdb_regs[GDB_R10]	= regs->r10;
	gdb_regs[GDB_R11]	= regs->r11;
	gdb_regs[GDB_R12]	= regs->r12;
	gdb_regs[GDB_R13]	= regs->r13;
	gdb_regs[GDB_R14]	= regs->r14;
	gdb_regs[GDB_R15]	= regs->r15;
	gdb_regs32[GDB_PS]	= regs->flags;
	gdb_regs32[GDB_CS]	= regs->cs;
	gdb_regs32[GDB_SS]	= regs->ss;
	gdb_regs[GDB_SP]	= regs->sp;
#endif
}