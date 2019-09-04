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
typedef  int /*<<< orphan*/  run_queue_t ;
typedef  scalar_t__ processor_t ;
struct TYPE_3__ {scalar_t__ bound_processor; } ;

/* Variables and functions */
 scalar_t__ PROCESSOR_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dualq_bound_runq (scalar_t__) ; 
 int /*<<< orphan*/  dualq_main_runq (scalar_t__) ; 

__attribute__((used)) __attribute__((always_inline))
static inline run_queue_t dualq_runq_for_thread(processor_t processor, thread_t thread)
{
	if (thread->bound_processor == PROCESSOR_NULL) {
		return dualq_main_runq(processor);
	} else {
		assert(thread->bound_processor == processor);
		return dualq_bound_runq(processor);
	}
}