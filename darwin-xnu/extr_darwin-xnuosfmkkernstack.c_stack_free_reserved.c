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
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {scalar_t__ reserved_stack; scalar_t__ kernel_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  stack_free_stack (scalar_t__) ; 

void
stack_free_reserved(
	thread_t	thread)
{
	if (thread->reserved_stack != thread->kernel_stack) {
		stack_free_stack(thread->reserved_stack);
	}
}