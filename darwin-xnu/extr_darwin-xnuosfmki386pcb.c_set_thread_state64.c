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
struct TYPE_7__ {int rflags; scalar_t__ gs; scalar_t__ fs; int /*<<< orphan*/  rip; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; } ;
typedef  TYPE_2__ x86_thread_state64_t ;
struct TYPE_6__ {int rflags; int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  rsp; } ;
struct TYPE_8__ {void* gs; void* fs; TYPE_1__ isf; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY ; 
 int EFL_USER_CLEAR ; 
 int EFL_USER_SET ; 
 int /*<<< orphan*/  IS_USERADDR64_CANONICAL (int /*<<< orphan*/ ) ; 
 int KERN_INVALID_ARGUMENT ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  USER64_CS ; 
 TYPE_3__* USER_REGS64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_thread_state64(thread_t thread, x86_thread_state64_t *ts)
{
        x86_saved_state64_t	*saved_state;

	pal_register_cache_state(thread, DIRTY);

	saved_state = USER_REGS64(thread);

	if (!IS_USERADDR64_CANONICAL(ts->rsp) ||
	    !IS_USERADDR64_CANONICAL(ts->rip))
		return(KERN_INVALID_ARGUMENT);

	saved_state->r8 = ts->r8;
	saved_state->r9 = ts->r9;
	saved_state->r10 = ts->r10;
	saved_state->r11 = ts->r11;
	saved_state->r12 = ts->r12;
	saved_state->r13 = ts->r13;
	saved_state->r14 = ts->r14;
	saved_state->r15 = ts->r15;
	saved_state->rax = ts->rax;
	saved_state->rbx = ts->rbx;
	saved_state->rcx = ts->rcx;
	saved_state->rdx = ts->rdx;
	saved_state->rdi = ts->rdi;
	saved_state->rsi = ts->rsi;
	saved_state->rbp = ts->rbp;
	saved_state->isf.rsp = ts->rsp;
	saved_state->isf.rflags = (ts->rflags & ~EFL_USER_CLEAR) | EFL_USER_SET;
	saved_state->isf.rip = ts->rip;
	saved_state->isf.cs = USER64_CS;
	saved_state->fs = (uint32_t)ts->fs;
	saved_state->gs = (uint32_t)ts->gs;

	return(KERN_SUCCESS);
}