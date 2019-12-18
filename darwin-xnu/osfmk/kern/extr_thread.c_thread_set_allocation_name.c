#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_kernel_state_t ;
typedef  scalar_t__ kern_allocation_name_t ;
struct TYPE_3__ {scalar_t__ allocation_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 TYPE_1__* thread_get_kernel_state (int /*<<< orphan*/ ) ; 

kern_allocation_name_t thread_set_allocation_name(kern_allocation_name_t new_name)
{
	kern_allocation_name_t ret;
	thread_kernel_state_t kstate = thread_get_kernel_state(current_thread());
	ret = kstate->allocation_name;
	// fifo
	if (!new_name || !kstate->allocation_name) kstate->allocation_name = new_name;
	return ret;
}