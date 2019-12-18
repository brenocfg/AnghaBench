#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stack_trace {int dummy; } ;
struct TYPE_2__ {scalar_t__ thread_info; scalar_t__ async_stack; scalar_t__ panic_stack; } ;

/* Variables and functions */
 scalar_t__ ASYNC_SIZE ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long PSW_ADDR_INSN ; 
 TYPE_1__ S390_lowcore ; 
 scalar_t__ THREAD_SIZE ; 
 unsigned long save_context_stack (struct stack_trace*,unsigned long,scalar_t__,scalar_t__,int) ; 

void save_stack_trace(struct stack_trace *trace)
{
	register unsigned long sp asm ("15");
	unsigned long orig_sp, new_sp;

	orig_sp = sp & PSW_ADDR_INSN;
	new_sp = save_context_stack(trace, orig_sp,
				    S390_lowcore.panic_stack - PAGE_SIZE,
				    S390_lowcore.panic_stack, 1);
	if (new_sp != orig_sp)
		return;
	new_sp = save_context_stack(trace, new_sp,
				    S390_lowcore.async_stack - ASYNC_SIZE,
				    S390_lowcore.async_stack, 1);
	if (new_sp != orig_sp)
		return;
	save_context_stack(trace, new_sp,
			   S390_lowcore.thread_info,
			   S390_lowcore.thread_info + THREAD_SIZE, 1);
}