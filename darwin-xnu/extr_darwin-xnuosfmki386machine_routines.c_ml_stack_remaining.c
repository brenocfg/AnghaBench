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
typedef  scalar_t__ vm_offset_t ;
struct TYPE_4__ {scalar_t__ cpu_int_stack_top; } ;
struct TYPE_3__ {scalar_t__ kernel_stack; } ;

/* Variables and functions */
 scalar_t__ INTSTACK_SIZE ; 
 TYPE_2__* current_cpu_datap () ; 
 TYPE_1__* current_thread () ; 
 uintptr_t local ; 
 scalar_t__ ml_at_interrupt_context () ; 

vm_offset_t ml_stack_remaining(void)
{
	uintptr_t local = (uintptr_t) &local;

	if (ml_at_interrupt_context() != 0) {
	    return (local - (current_cpu_datap()->cpu_int_stack_top - INTSTACK_SIZE));
	} else {
	    return (local - current_thread()->kernel_stack);
	}
}