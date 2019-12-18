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
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {scalar_t__ kernel_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  machine_stack_attach (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_alloc_internal () ; 

void
stack_alloc(
	thread_t	thread)
{

	assert(thread->kernel_stack == 0);
	machine_stack_attach(thread, stack_alloc_internal());
}