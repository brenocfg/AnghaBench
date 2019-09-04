#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int fs; int gs; int /*<<< orphan*/  cs; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rip; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;
struct TYPE_16__ {int ds; int es; int fs; int gs; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  eip; int /*<<< orphan*/  eflags; int /*<<< orphan*/  esp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
struct TYPE_20__ {TYPE_4__ ts64; TYPE_1__ ts32; } ;
struct TYPE_17__ {int flavor; void* count; } ;
struct TYPE_21__ {TYPE_5__ uts; TYPE_2__ tsh; } ;
typedef  TYPE_6__ x86_thread_state_t ;
struct TYPE_22__ {int fs; int gs; int /*<<< orphan*/  cs; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rip; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;
typedef  TYPE_7__ x86_thread_state64_t ;
struct TYPE_23__ {int ds; int es; int fs; int gs; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  eip; int /*<<< orphan*/  eflags; int /*<<< orphan*/  esp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
typedef  TYPE_8__ x86_thread_state32_t ;
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_18__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rip; int /*<<< orphan*/  rsp; } ;
struct TYPE_24__ {int fs; int gs; TYPE_3__ isf; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;
typedef  TYPE_9__ x86_saved_state64_t ;
struct TYPE_14__ {int ds; int es; int fs; int gs; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  eip; int /*<<< orphan*/  efl; int /*<<< orphan*/  uesp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
typedef  TYPE_10__ x86_saved_state32_t ;
typedef  scalar_t__ thread_t ;
typedef  scalar_t__ thread_state_t ;
typedef  int thread_flavor_t ;
typedef  void* mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_15__ {int /*<<< orphan*/ * cpu_int_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_13__* current_cpu_datap () ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  is_saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_10__* saved_state32 (int /*<<< orphan*/ *) ; 
 TYPE_9__* saved_state64 (int /*<<< orphan*/ *) ; 
#define  x86_THREAD_STATE 130 
#define  x86_THREAD_STATE32 129 
 void* x86_THREAD_STATE32_COUNT ; 
#define  x86_THREAD_STATE64 128 
 void* x86_THREAD_STATE64_COUNT ; 
 void* x86_THREAD_STATE_COUNT ; 

kern_return_t
machine_thread_get_kern_state(
		thread_t		thread,
		thread_flavor_t		flavor,
		thread_state_t		tstate,
		mach_msg_type_number_t	*count)
{
	x86_saved_state_t	*int_state = current_cpu_datap()->cpu_int_state;

	/*
	 * This works only for an interrupted kernel thread
	 */
	if (thread != current_thread() || int_state == NULL)
		return KERN_FAILURE;

	switch (flavor) {
	    case x86_THREAD_STATE32: {
		x86_thread_state32_t *state;
		x86_saved_state32_t *saved_state;

		if (!is_saved_state32(int_state) ||
		    *count < x86_THREAD_STATE32_COUNT)
			return (KERN_INVALID_ARGUMENT);

		state = (x86_thread_state32_t *) tstate;

		saved_state = saved_state32(int_state);
		/*
		 * General registers.
		 */
		state->eax = saved_state->eax;
		state->ebx = saved_state->ebx;
		state->ecx = saved_state->ecx;
		state->edx = saved_state->edx;
		state->edi = saved_state->edi;
		state->esi = saved_state->esi;
		state->ebp = saved_state->ebp;
		state->esp = saved_state->uesp;
		state->eflags = saved_state->efl;
		state->eip = saved_state->eip;
		state->cs = saved_state->cs;
		state->ss = saved_state->ss;
		state->ds = saved_state->ds & 0xffff;
		state->es = saved_state->es & 0xffff;
		state->fs = saved_state->fs & 0xffff;
		state->gs = saved_state->gs & 0xffff;

		*count = x86_THREAD_STATE32_COUNT;

		return KERN_SUCCESS;
	    }
  
	    case x86_THREAD_STATE64: {
		x86_thread_state64_t	*state;
		x86_saved_state64_t	*saved_state;

		if (!is_saved_state64(int_state) ||
		    *count < x86_THREAD_STATE64_COUNT)
			return (KERN_INVALID_ARGUMENT);

		state = (x86_thread_state64_t *) tstate;

		saved_state = saved_state64(int_state);
		/*
		 * General registers.
		 */
		state->rax = saved_state->rax;
		state->rbx = saved_state->rbx;
		state->rcx = saved_state->rcx;
		state->rdx = saved_state->rdx;
		state->rdi = saved_state->rdi;
		state->rsi = saved_state->rsi;
		state->rbp = saved_state->rbp;
		state->rsp = saved_state->isf.rsp;
		state->r8 = saved_state->r8;
		state->r9 = saved_state->r9;
		state->r10 = saved_state->r10;
		state->r11 = saved_state->r11;
		state->r12 = saved_state->r12;
		state->r13 = saved_state->r13;
		state->r14 = saved_state->r14;
		state->r15 = saved_state->r15;

		state->rip = saved_state->isf.rip;
		state->rflags = saved_state->isf.rflags;
		state->cs = saved_state->isf.cs;
		state->fs = saved_state->fs & 0xffff;
		state->gs = saved_state->gs & 0xffff;
		*count = x86_THREAD_STATE64_COUNT;

		return KERN_SUCCESS;
	    }
  
	    case x86_THREAD_STATE: {
		x86_thread_state_t *state = NULL;

		if (*count < x86_THREAD_STATE_COUNT)
			return (KERN_INVALID_ARGUMENT);

		state = (x86_thread_state_t *) tstate;

		if (is_saved_state32(int_state)) {
			x86_saved_state32_t *saved_state = saved_state32(int_state);

			state->tsh.flavor = x86_THREAD_STATE32;
			state->tsh.count = x86_THREAD_STATE32_COUNT;

			/*
			 * General registers.
			 */
			state->uts.ts32.eax = saved_state->eax;
			state->uts.ts32.ebx = saved_state->ebx;
			state->uts.ts32.ecx = saved_state->ecx;
			state->uts.ts32.edx = saved_state->edx;
			state->uts.ts32.edi = saved_state->edi;
			state->uts.ts32.esi = saved_state->esi;
			state->uts.ts32.ebp = saved_state->ebp;
			state->uts.ts32.esp = saved_state->uesp;
			state->uts.ts32.eflags = saved_state->efl;
			state->uts.ts32.eip = saved_state->eip;
			state->uts.ts32.cs = saved_state->cs;
			state->uts.ts32.ss = saved_state->ss;
			state->uts.ts32.ds = saved_state->ds & 0xffff;
			state->uts.ts32.es = saved_state->es & 0xffff;
			state->uts.ts32.fs = saved_state->fs & 0xffff;
			state->uts.ts32.gs = saved_state->gs & 0xffff;
		} else if (is_saved_state64(int_state)) {
			x86_saved_state64_t *saved_state = saved_state64(int_state);

			state->tsh.flavor = x86_THREAD_STATE64;
			state->tsh.count = x86_THREAD_STATE64_COUNT;

			/*
			 * General registers.
			 */
			state->uts.ts64.rax = saved_state->rax;
			state->uts.ts64.rbx = saved_state->rbx;
			state->uts.ts64.rcx = saved_state->rcx;
			state->uts.ts64.rdx = saved_state->rdx;
			state->uts.ts64.rdi = saved_state->rdi;
			state->uts.ts64.rsi = saved_state->rsi;
			state->uts.ts64.rbp = saved_state->rbp;
			state->uts.ts64.rsp = saved_state->isf.rsp;
			state->uts.ts64.r8 = saved_state->r8;
			state->uts.ts64.r9 = saved_state->r9;
			state->uts.ts64.r10 = saved_state->r10;
			state->uts.ts64.r11 = saved_state->r11;
			state->uts.ts64.r12 = saved_state->r12;
			state->uts.ts64.r13 = saved_state->r13;
			state->uts.ts64.r14 = saved_state->r14;
			state->uts.ts64.r15 = saved_state->r15;

			state->uts.ts64.rip = saved_state->isf.rip;
			state->uts.ts64.rflags = saved_state->isf.rflags;
			state->uts.ts64.cs = saved_state->isf.cs;
			state->uts.ts64.fs = saved_state->fs & 0xffff;
			state->uts.ts64.gs = saved_state->gs & 0xffff;
		} else {
			panic("unknown thread state");
		}

		*count = x86_THREAD_STATE_COUNT;
		return KERN_SUCCESS;
	    }
	}
	return KERN_FAILURE;
}