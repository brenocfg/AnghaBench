#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int FPSCR; int* GPR; int MSR; int LR; } ;
struct TYPE_6__ {int stack_size; int isr_level; TYPE_1__ context; scalar_t__ stack; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
 int CPU_MINIMUM_STACK_FRAME_SIZE ; 
 int CPU_MODES_INTERRUPT_MASK ; 
 int CPU_STACK_ALIGNMENT ; 
 int MSR_DR ; 
 int MSR_EE ; 
 int MSR_IR ; 
 int MSR_ME ; 
 int MSR_RI ; 
 scalar_t__ __lwp_thread_handler ; 
 int /*<<< orphan*/  kprintf (char*,TYPE_2__*,void*,int,void*) ; 

void __lwp_thread_loadenv(lwp_cntrl *thethread)
{
	u32 stackbase,sp,size;
	u32 r2,r13,msr_value;

	thethread->context.FPSCR = 0x000000f8;

	stackbase = (u32)thethread->stack;
	size = thethread->stack_size;

	// tag both bottom & head of stack
	*((u32*)stackbase) = 0xDEADBABE;
	sp = stackbase+size-CPU_MINIMUM_STACK_FRAME_SIZE;
	sp &= ~(CPU_STACK_ALIGNMENT-1);
	*((u32*)sp) = 0;

	thethread->context.GPR[1] = sp;

	msr_value = (MSR_ME|MSR_IR|MSR_DR|MSR_RI);
	if(!(thethread->isr_level&CPU_MODES_INTERRUPT_MASK))
		msr_value |= MSR_EE;

	thethread->context.MSR = msr_value;
	thethread->context.LR = (u32)__lwp_thread_handler;

	__asm__ __volatile__ ("mr %0,2; mr %1,13" : "=r" ((r2)), "=r" ((r13)));
	thethread->context.GPR[2] = r2;
	thethread->context.GPR[13] = r13;

#ifdef _LWPTHREADS_DEBUG
	kprintf("__lwp_thread_loadenv(%p,%p,%d,%p)\n",thethread,(void*)stackbase,size,(void*)sp);
#endif

}