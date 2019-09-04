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
 int /*<<< orphan*/  assert (int) ; 
 int dateNow ; 
 int emscripten_date_now () ; 
 int emscripten_performance_now () ; 
 int /*<<< orphan*/  emscripten_set_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int performanceNow ; 
 int /*<<< orphan*/  test ; 

int main()
{
	performanceNow = emscripten_performance_now();
	assert(performanceNow < 10*1000); // Should take well less than 10 seconds to load up the page

	dateNow = emscripten_date_now();
	assert(dateNow > 1547568082); // == 2019-01-15T16:01:22+00:00)

#ifdef __EMSCRIPTEN_PTHREADS__
	emscripten_thread_sleep(200);
	test(0);
#else
	emscripten_set_timeout(test, 200, 0);
#endif
}