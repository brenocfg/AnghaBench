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
struct TYPE_6__ {int /*<<< orphan*/  rsp; int /*<<< orphan*/  rip; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; } ;
typedef  TYPE_2__ x86_thread_state64_t ;
struct TYPE_5__ {int /*<<< orphan*/  rflags; int /*<<< orphan*/  cs; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rip; } ;
struct TYPE_7__ {TYPE_1__ isf; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; scalar_t__ rbp; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
typedef  scalar_t__ thread_t ;
typedef  scalar_t__ thread_state_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY ; 
 int /*<<< orphan*/  EFL_USER_SET ; 
 int /*<<< orphan*/  IS_USERADDR64_CANONICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  USER64_CS ; 
 TYPE_3__* USER_REGS64 (scalar_t__) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  pal_register_cache_state (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (scalar_t__) ; 
 int /*<<< orphan*/  thread_unlock (scalar_t__) ; 

kern_return_t
thread_set_wq_state64(thread_t thread, thread_state_t tstate)
{
        x86_thread_state64_t	*state;
        x86_saved_state64_t	*saved_state;
	thread_t curth = current_thread();
	spl_t			s=0;

	saved_state = USER_REGS64(thread);
	state = (x86_thread_state64_t *)tstate;
	
	/* Disallow setting non-canonical PC or stack */
	if (!IS_USERADDR64_CANONICAL(state->rsp) ||
	    !IS_USERADDR64_CANONICAL(state->rip)) {
		return KERN_FAILURE;
	}

	pal_register_cache_state(thread, DIRTY);

	if (curth != thread) {
		s = splsched();
	        thread_lock(thread);
	}

	saved_state->rbp = 0;
	saved_state->rdi = state->rdi;
	saved_state->rsi = state->rsi;
	saved_state->rdx = state->rdx;
	saved_state->rcx = state->rcx;
	saved_state->r8  = state->r8;
	saved_state->r9  = state->r9;

	saved_state->isf.rip = state->rip;
	saved_state->isf.rsp = state->rsp;
	saved_state->isf.cs = USER64_CS;
	saved_state->isf.rflags = EFL_USER_SET;

	if (curth != thread) {
	        thread_unlock(thread);
		splx(s);
	}

	return KERN_SUCCESS;
}