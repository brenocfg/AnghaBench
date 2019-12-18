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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PERF_TI_CSWITCH ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ ) ; 
 scalar_t__ kperf_kdebug_cswitch ; 
 scalar_t__ kperf_lazy_wait_action ; 
 int /*<<< orphan*/  kperf_lazy_wait_sample (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 scalar_t__ kperf_lightweight_pet_active ; 
 int /*<<< orphan*/  kperf_pet_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int task_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 

void
kperf_on_cpu_internal(thread_t thread, thread_continue_t continuation,
                      uintptr_t *starting_fp)
{
	if (kperf_kdebug_cswitch) {
		/* trace the new thread's PID for Instruments */
		int pid = task_pid(get_threadtask(thread));
		BUF_DATA(PERF_TI_CSWITCH, thread_tid(thread), pid);
	}
	if (kperf_lightweight_pet_active) {
		kperf_pet_on_cpu(thread, continuation, starting_fp);
	}
	if (kperf_lazy_wait_action != 0) {
		kperf_lazy_wait_sample(thread, continuation, starting_fp);
	}
}