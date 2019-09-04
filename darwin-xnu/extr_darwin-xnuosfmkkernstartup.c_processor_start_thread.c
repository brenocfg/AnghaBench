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
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  TYPE_1__* processor_t ;
struct TYPE_3__ {scalar_t__ idle_thread; } ;

/* Variables and functions */
 TYPE_1__* current_processor () ; 
 scalar_t__ current_thread () ; 
 scalar_t__ idle_thread ; 
 int /*<<< orphan*/  slave_machine_init (void*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_terminate (scalar_t__) ; 

void
processor_start_thread(void *machine_param)
{
	processor_t		processor = current_processor();
	thread_t		self = current_thread();

	slave_machine_init(machine_param);

	/*
	 *	If running the idle processor thread,
	 *	reenter the idle loop, else terminate.
	 */
	if (self == processor->idle_thread)
		thread_block((thread_continue_t)idle_thread);

	thread_terminate(self);
	/*NOTREACHED*/
}