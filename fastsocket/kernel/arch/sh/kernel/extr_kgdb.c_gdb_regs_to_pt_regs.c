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
struct pt_regs {unsigned long* regs; unsigned long pc; unsigned long pr; unsigned long sr; unsigned long gbr; unsigned long mach; unsigned long macl; } ;

/* Variables and functions */
 size_t GDB_GBR ; 
 size_t GDB_MACH ; 
 size_t GDB_MACL ; 
 size_t GDB_PC ; 
 size_t GDB_PR ; 
 int GDB_R0 ; 
 size_t GDB_SR ; 

void gdb_regs_to_pt_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	int i;

	for (i = 0; i < 16; i++)
		regs->regs[GDB_R0 + i] = gdb_regs[GDB_R0 + i];

	regs->pc = gdb_regs[GDB_PC];
	regs->pr = gdb_regs[GDB_PR];
	regs->sr = gdb_regs[GDB_SR];
	regs->gbr = gdb_regs[GDB_GBR];
	regs->mach = gdb_regs[GDB_MACH];
	regs->macl = gdb_regs[GDB_MACL];
}