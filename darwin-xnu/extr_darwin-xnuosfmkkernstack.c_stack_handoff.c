#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  machine_stack_handoff (scalar_t__,scalar_t__) ; 

void
stack_handoff(thread_t from, thread_t to)
{
	assert(from == current_thread());
	machine_stack_handoff(from, to);
}