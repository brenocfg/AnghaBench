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

/* Variables and functions */
 int /*<<< orphan*/  EM_THREAD_STATUS_RUNNING ; 
 int /*<<< orphan*/  EM_THREAD_STATUS_SLEEPING ; 
 int /*<<< orphan*/  __pthread_testcancel () ; 
 int /*<<< orphan*/  dummyZeroAddress ; 
 int /*<<< orphan*/  emscripten_conditional_set_current_thread_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_current_thread_process_queued_calls () ; 
 int /*<<< orphan*/  emscripten_futex_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 double emscripten_get_now () ; 
 scalar_t__ emscripten_is_main_browser_thread () ; 

void emscripten_thread_sleep(double msecs)
{
	double now = emscripten_get_now();
	double target = now + msecs;

	__pthread_testcancel(); // pthreads spec: sleep is a cancellation point, so must test if this thread is cancelled during the sleep.
	emscripten_current_thread_process_queued_calls();

	// If we have less than this many msecs left to wait, busy spin that instead.
	const double minimumTimeSliceToSleep = 0.1;

	// main thread may need to run proxied calls, so sleep in very small slices to be responsive.
	const double maxMsecsSliceToSleep = emscripten_is_main_browser_thread() ? 1 : 100;

	emscripten_conditional_set_current_thread_status(EM_THREAD_STATUS_RUNNING, EM_THREAD_STATUS_SLEEPING);
	now = emscripten_get_now();
	while(now < target)
	{
		// Keep processing the main loop of the calling thread.
		__pthread_testcancel(); // pthreads spec: sleep is a cancellation point, so must test if this thread is cancelled during the sleep.
		emscripten_current_thread_process_queued_calls();

		now = emscripten_get_now();
		double msecsToSleep = target - now;
		if (msecsToSleep > maxMsecsSliceToSleep) msecsToSleep = maxMsecsSliceToSleep;
		if (msecsToSleep >= minimumTimeSliceToSleep) emscripten_futex_wait(&dummyZeroAddress, 0, msecsToSleep);
		now = emscripten_get_now();
	};

	emscripten_conditional_set_current_thread_status(EM_THREAD_STATUS_SLEEPING, EM_THREAD_STATUS_RUNNING);
}