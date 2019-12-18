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
struct TYPE_5__ {int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rsp; } ;
struct TYPE_6__ {TYPE_1__ isf; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;
struct TYPE_7__ {TYPE_2__ ss_64; } ;
typedef  TYPE_3__ x86_saved_state_t ;
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 TYPE_3__* get_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
print_threads_registers(thread_t thread)
{
	x86_saved_state_t *savestate;
	
	savestate = get_user_regs(thread);
	paniclog_append_noflush(
		"\nRAX: 0x%016llx, RBX: 0x%016llx, RCX: 0x%016llx, RDX: 0x%016llx\n"
	    "RSP: 0x%016llx, RBP: 0x%016llx, RSI: 0x%016llx, RDI: 0x%016llx\n"
	    "R8:  0x%016llx, R9:  0x%016llx, R10: 0x%016llx, R11: 0x%016llx\n"
		"R12: 0x%016llx, R13: 0x%016llx, R14: 0x%016llx, R15: 0x%016llx\n"
		"RFL: 0x%016llx, RIP: 0x%016llx, CS:  0x%016llx, SS:  0x%016llx\n\n",
		savestate->ss_64.rax, savestate->ss_64.rbx, savestate->ss_64.rcx, savestate->ss_64.rdx,
		savestate->ss_64.isf.rsp, savestate->ss_64.rbp, savestate->ss_64.rsi, savestate->ss_64.rdi,
		savestate->ss_64.r8, savestate->ss_64.r9,  savestate->ss_64.r10, savestate->ss_64.r11,
		savestate->ss_64.r12, savestate->ss_64.r13, savestate->ss_64.r14, savestate->ss_64.r15,
		savestate->ss_64.isf.rflags, savestate->ss_64.isf.rip, savestate->ss_64.isf.cs,
		savestate->ss_64.isf.ss);
}