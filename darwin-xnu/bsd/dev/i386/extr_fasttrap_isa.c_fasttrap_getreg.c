#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  ss; int /*<<< orphan*/  rflags; int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  err; int /*<<< orphan*/  trapno; int /*<<< orphan*/  rsp; } ;
struct TYPE_7__ {int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; TYPE_1__ isf; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rax; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
struct TYPE_8__ {int /*<<< orphan*/  edi; int /*<<< orphan*/  esi; int /*<<< orphan*/  ebp; int /*<<< orphan*/  uesp; int /*<<< orphan*/  ebx; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  eax; } ;
typedef  TYPE_3__ x86_saved_state32_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint_t ;

/* Variables and functions */
#define  REG_CS 155 
#define  REG_DS 154 
#define  REG_ERR 153 
#define  REG_ES 152 
#define  REG_FS 151 
#define  REG_FSBASE 150 
#define  REG_GS 149 
#define  REG_GSBASE 148 
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
 scalar_t__ is_saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_3__* saved_state32 (int /*<<< orphan*/ *) ; 
 TYPE_2__* saved_state64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static user_addr_t
fasttrap_getreg(x86_saved_state_t *regs, uint_t reg)
{
	if (is_saved_state64(regs)) {
		x86_saved_state64_t *regs64 = saved_state64(regs);

		switch (reg) {
			case REG_RAX:		return regs64->rax;
			case REG_RCX:		return regs64->rcx;
			case REG_RDX:		return regs64->rdx;
			case REG_RBX:		return regs64->rbx;
			case REG_RSP:		return regs64->isf.rsp;
			case REG_RBP:		return regs64->rbp;
			case REG_RSI:		return regs64->rsi;
			case REG_RDI:		return regs64->rdi;
			case REG_R8:		return regs64->r8;
			case REG_R9:		return regs64->r9;
			case REG_R10:		return regs64->r10;
			case REG_R11:		return regs64->r11;
			case REG_R12:		return regs64->r12;
			case REG_R13:		return regs64->r13;
			case REG_R14:		return regs64->r14;
			case REG_R15:		return regs64->r15;
			case REG_TRAPNO:	return regs64->isf.trapno;
			case REG_ERR:		return regs64->isf.err;
			case REG_RIP:		return regs64->isf.rip;
			case REG_CS:		return regs64->isf.cs;
			case REG_RFL:		return regs64->isf.rflags;
			case REG_SS:		return regs64->isf.ss;
			case REG_FS:		return regs64->fs;
			case REG_GS:		return regs64->gs;
			case REG_ES:
			case REG_DS:
			case REG_FSBASE:
			case REG_GSBASE:
				// Important to distinguish these requests (which should be legal) from other values.
				panic("dtrace: unimplemented x86_64 getreg()");
		}

		panic("dtrace: unhandled x86_64 getreg() constant");
	} else {
		x86_saved_state32_t *regs32 = saved_state32(regs);

		switch (reg) {
			case REG_RAX:		return regs32->eax;
			case REG_RCX:		return regs32->ecx;
			case REG_RDX:		return regs32->edx;
			case REG_RBX:		return regs32->ebx;
			case REG_RSP:		return regs32->uesp;
			case REG_RBP:		return regs32->ebp;
			case REG_RSI:		return regs32->esi;
			case REG_RDI:		return regs32->edi;
		}

		panic("dtrace: unhandled i386 getreg() constant");
	}

	return 0;
}