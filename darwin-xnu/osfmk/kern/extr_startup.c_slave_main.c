#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ thread_continue_t ;
typedef  TYPE_2__* processor_t ;
struct TYPE_7__ {TYPE_1__* next_thread; TYPE_1__* idle_thread; } ;
struct TYPE_6__ {void* parameter; scalar_t__ continuation; } ;

/* Variables and functions */
 TYPE_1__* THREAD_NULL ; 
 TYPE_2__* current_processor () ; 
 int /*<<< orphan*/  load_context (TYPE_1__*) ; 
 scalar_t__ processor_start_thread ; 

void
slave_main(void *machine_param)
{
	processor_t		processor = current_processor();
	thread_t		thread;

	/*
	 *	Use the idle processor thread if there
	 *	is no dedicated start up thread.
	 */
	if (processor->next_thread == THREAD_NULL) {
		thread = processor->idle_thread;
		thread->continuation = (thread_continue_t)processor_start_thread;
		thread->parameter = machine_param;
	}
	else {
		thread = processor->next_thread;
		processor->next_thread = THREAD_NULL;
	}

	load_context(thread);
	/*NOTREACHED*/
}