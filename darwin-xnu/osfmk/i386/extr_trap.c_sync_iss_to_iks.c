#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ flavor; } ;
typedef  TYPE_2__ x86_saved_state_t ;
struct TYPE_11__ {int /*<<< orphan*/  rip; int /*<<< orphan*/  rsp; } ;
struct TYPE_13__ {TYPE_1__ isf; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rbx; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct x86_kernel_state {int /*<<< orphan*/  k_rip; int /*<<< orphan*/  k_r15; int /*<<< orphan*/  k_r14; int /*<<< orphan*/  k_r13; int /*<<< orphan*/  k_r12; int /*<<< orphan*/  k_rbp; int /*<<< orphan*/  k_rsp; int /*<<< orphan*/  k_rbx; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  kernel_stack; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 struct x86_kernel_state* STACK_IKS (int /*<<< orphan*/ ) ; 
 scalar_t__ THREAD_STATE_NONE ; 
 scalar_t__ TRUE ; 
 TYPE_3__* USER_REGS64 (TYPE_8__*) ; 
 TYPE_8__* current_thread () ; 
 int /*<<< orphan*/  pal_get_kern_regs (TYPE_2__*) ; 
 TYPE_3__* saved_state64 (TYPE_2__*) ; 

void
sync_iss_to_iks(x86_saved_state_t *saved_state)
{
	struct x86_kernel_state *iks = NULL;
	vm_offset_t kstack;
	boolean_t record_active_regs = FALSE;

	/* The PAL may have a special way to sync registers */
	if (saved_state && saved_state->flavor == THREAD_STATE_NONE)
		pal_get_kern_regs( saved_state );

	if (current_thread() != NULL && 
	    (kstack = current_thread()->kernel_stack) != 0) {
		x86_saved_state64_t	*regs = saved_state64(saved_state);

		iks = STACK_IKS(kstack);

		/* Did we take the trap/interrupt in kernel mode? */
		if (saved_state == NULL || /* NULL => polling in kernel */
		    regs == USER_REGS64(current_thread()))
		        record_active_regs = TRUE;
		else {
			iks->k_rbx = regs->rbx;
			iks->k_rsp = regs->isf.rsp;
			iks->k_rbp = regs->rbp;
			iks->k_r12 = regs->r12;
			iks->k_r13 = regs->r13;
			iks->k_r14 = regs->r14;
			iks->k_r15 = regs->r15;
			iks->k_rip = regs->isf.rip;
		}
	}

	if (record_active_regs == TRUE) {
		/* Show the trap handler path */
		__asm__ volatile("movq %%rbx, %0" : "=m" (iks->k_rbx));
		__asm__ volatile("movq %%rsp, %0" : "=m" (iks->k_rsp));
		__asm__ volatile("movq %%rbp, %0" : "=m" (iks->k_rbp));
		__asm__ volatile("movq %%r12, %0" : "=m" (iks->k_r12));
		__asm__ volatile("movq %%r13, %0" : "=m" (iks->k_r13));
		__asm__ volatile("movq %%r14, %0" : "=m" (iks->k_r14));
		__asm__ volatile("movq %%r15, %0" : "=m" (iks->k_r15));
		/* "Current" instruction pointer */
		__asm__ volatile("leaq 1f(%%rip), %%rax; mov %%rax, %0\n1:"
				 : "=m" (iks->k_rip)
				 :
				 : "rax");
	}
}