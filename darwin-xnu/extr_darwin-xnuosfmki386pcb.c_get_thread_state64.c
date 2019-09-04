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
struct TYPE_7__ {int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; } ;
typedef  TYPE_2__ x86_thread_state64_t ;
struct TYPE_6__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rsp; } ;
struct TYPE_8__ {int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; TYPE_1__ isf; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 TYPE_3__* USER_REGS64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_thread_state64(thread_t thread, x86_thread_state64_t *ts)
{
        x86_saved_state64_t	*saved_state;

	pal_register_cache_state(thread, VALID);

	saved_state = USER_REGS64(thread);

	ts->r8 = saved_state->r8;
	ts->r9 = saved_state->r9;
	ts->r10 = saved_state->r10;
	ts->r11 = saved_state->r11;
	ts->r12 = saved_state->r12;
	ts->r13 = saved_state->r13;
	ts->r14 = saved_state->r14;
	ts->r15 = saved_state->r15;
	ts->rax = saved_state->rax;
	ts->rbx = saved_state->rbx;
	ts->rcx = saved_state->rcx;
	ts->rdx = saved_state->rdx;
	ts->rdi = saved_state->rdi;
	ts->rsi = saved_state->rsi;
	ts->rbp = saved_state->rbp;
	ts->rsp = saved_state->isf.rsp;
	ts->rflags = saved_state->isf.rflags;
	ts->rip = saved_state->isf.rip;
	ts->cs = saved_state->isf.cs;
	ts->fs = saved_state->fs;
	ts->gs = saved_state->gs;
}