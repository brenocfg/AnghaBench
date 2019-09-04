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
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PERF_PET_IDLE ; 
 int /*<<< orphan*/  PERF_PET_RUN ; 
 int /*<<< orphan*/  PERF_PET_THREAD ; 
 int /*<<< orphan*/  kperf_timer_pet_rearm (scalar_t__) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  pet_lock ; 
 int /*<<< orphan*/  pet_thread_idle () ; 
 int /*<<< orphan*/  pet_thread_work_unit () ; 

__attribute__((used)) __attribute__((noreturn))
static void
pet_thread_loop(void *param, wait_result_t wr)
{
#pragma unused(param, wr)
	uint64_t work_unit_ticks;

	BUF_INFO(PERF_PET_THREAD, 1);

	lck_mtx_lock(pet_lock);
	for (;;) {
		BUF_INFO(PERF_PET_IDLE);
		pet_thread_idle();

		BUF_INFO(PERF_PET_RUN);

		/* measure how long the work unit takes */
		work_unit_ticks = mach_absolute_time();
		pet_thread_work_unit();
		work_unit_ticks = mach_absolute_time() - work_unit_ticks;

		/* re-program the timer */
		kperf_timer_pet_rearm(work_unit_ticks);
	}
}