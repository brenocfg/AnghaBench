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
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/ * processor_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  system_timer; int /*<<< orphan*/  user_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PROCESSOR_DATA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current_processor () ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_timer ; 
 scalar_t__ timer_grab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t thread_get_runtime_self(void)
{
	boolean_t interrupt_state;
	uint64_t runtime;
	thread_t thread = NULL;
	processor_t processor = NULL;

	thread = current_thread();

	/* Not interrupt safe, as the scheduler may otherwise update timer values underneath us */
	interrupt_state = ml_set_interrupts_enabled(FALSE);
	processor = current_processor();
	timer_update(PROCESSOR_DATA(processor, thread_timer), mach_absolute_time());
	runtime = (timer_grab(&thread->user_timer) + timer_grab(&thread->system_timer));
	ml_set_interrupts_enabled(interrupt_state);

	return runtime;
}