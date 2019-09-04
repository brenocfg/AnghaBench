#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gs; } ;
struct TYPE_5__ {int /*<<< orphan*/  rsp; int /*<<< orphan*/  rflags; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  err; int /*<<< orphan*/  trapno; } ;
struct TYPE_6__ {TYPE_1__ isf; int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; } ;
struct TYPE_8__ {TYPE_3__ ss_32; TYPE_2__ ss_64; } ;
typedef  TYPE_4__ x86_saved_state_t ;
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct regs {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
#define  REG_CS 153 
#define  REG_DS 152 
#define  REG_ERR 151 
#define  REG_ES 150 
#define  REG_FS 149 
#define  REG_GS 148 
#define  REG_R10 147 
#define  REG_R11 146 
#define  REG_R12 145 
#define  REG_R13 144 
#define  REG_R14 143 
#define  REG_R15 142 
#define  REG_R8 141 
#define  REG_R9 140 
#define  REG_RAX 139 
#define  REG_RBP 138 
#define  REG_RBX 137 
#define  REG_RCX 136 
#define  REG_RDI 135 
#define  REG_RDX 134 
#define  REG_RFL 133 
#define  REG_RIP 132 
#define  REG_RSI 131 
#define  REG_RSP 130 
#define  REG_SS 129 
#define  REG_TRAPNO 128 
 size_t SS ; 
 int /*<<< orphan*/  current_proc () ; 
 scalar_t__ proc_is64bit (int /*<<< orphan*/ ) ; 
 size_t* regmap ; 
 int x86_SAVED_STATE32_COUNT ; 

uint64_t
dtrace_getreg(struct regs *savearea, uint_t reg)
{
	boolean_t is64Bit = proc_is64bit(current_proc());
	x86_saved_state_t *regs = (x86_saved_state_t *)savearea;

	if (regs == NULL) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}

	if (is64Bit) {
	    if (reg <= SS) {
		reg = regmap[reg];
	    } else {
		reg -= (SS + 1);
	    }

	    switch (reg) {
	    case REG_RDI:
		return (uint64_t)(regs->ss_64.rdi);
	    case REG_RSI:
		return (uint64_t)(regs->ss_64.rsi);
	    case REG_RDX:
		return (uint64_t)(regs->ss_64.rdx);
	    case REG_RCX:
		return (uint64_t)(regs->ss_64.rcx);
	    case REG_R8:
		return (uint64_t)(regs->ss_64.r8);
	    case REG_R9:
		return (uint64_t)(regs->ss_64.r9);
	    case REG_RAX:
		return (uint64_t)(regs->ss_64.rax);
	    case REG_RBX:
		return (uint64_t)(regs->ss_64.rbx);
	    case REG_RBP:
		return (uint64_t)(regs->ss_64.rbp);
	    case REG_R10:
		return (uint64_t)(regs->ss_64.r10);
	    case REG_R11:
		return (uint64_t)(regs->ss_64.r11);
	    case REG_R12:
		return (uint64_t)(regs->ss_64.r12);
	    case REG_R13:
		return (uint64_t)(regs->ss_64.r13);
	    case REG_R14:
		return (uint64_t)(regs->ss_64.r14);
	    case REG_R15:
		return (uint64_t)(regs->ss_64.r15);
	    case REG_FS:
		return (uint64_t)(regs->ss_64.fs);
	    case REG_GS:
		return (uint64_t)(regs->ss_64.gs);
	    case REG_TRAPNO:
		return (uint64_t)(regs->ss_64.isf.trapno);
	    case REG_ERR:
		return (uint64_t)(regs->ss_64.isf.err);
	    case REG_RIP:
		return (uint64_t)(regs->ss_64.isf.rip);
	    case REG_CS:
		return (uint64_t)(regs->ss_64.isf.cs);
	    case REG_SS:
		return (uint64_t)(regs->ss_64.isf.ss);
	    case REG_RFL:
		return (uint64_t)(regs->ss_64.isf.rflags);
	    case REG_RSP:
		return (uint64_t)(regs->ss_64.isf.rsp);
	    case REG_DS:
	    case REG_ES:
	    default:
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	    }
	
	} else {   /* is 32bit user */
		/* beyond register SS */
		if (reg > x86_SAVED_STATE32_COUNT - 1) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
			return (0);
		}
		return (uint64_t)((unsigned int *)(&(regs->ss_32.gs)))[reg];
	}
}