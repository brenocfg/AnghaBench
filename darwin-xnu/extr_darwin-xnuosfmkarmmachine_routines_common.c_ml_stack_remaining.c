#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t vm_offset_t ;
struct TYPE_4__ {uintptr_t kernel_stack; } ;
struct TYPE_3__ {uintptr_t intstack_top; } ;

/* Variables and functions */
 uintptr_t INTSTACK_SIZE ; 
 TYPE_2__* current_thread () ; 
 TYPE_1__* getCpuDatap () ; 
 uintptr_t local ; 

vm_offset_t 
ml_stack_remaining(void)
{
	uintptr_t local = (uintptr_t) &local;
	vm_offset_t     intstack_top_ptr;

	/* Since this is a stack-based check, we don't need to worry about
	 * preemption as we do in ml_at_interrupt_context().  If we are preemptible,
	 * then the sp should never be within any CPU's interrupt stack unless
	 * something has gone horribly wrong. */
	intstack_top_ptr = getCpuDatap()->intstack_top;
	if ((local < intstack_top_ptr) && (local > intstack_top_ptr - INTSTACK_SIZE)) {
		return (local - (getCpuDatap()->intstack_top - INTSTACK_SIZE));
	} else {
		return (local - current_thread()->kernel_stack);
	}
}