#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {scalar_t__ reserved_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__ machine_stack_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  stack_free_stack (scalar_t__) ; 

void
stack_free(
	thread_t	thread)
{
    vm_offset_t		stack = machine_stack_detach(thread);

	assert(stack);
	if (stack != thread->reserved_stack) {
		stack_free_stack(stack);
	}
}