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
 double emscripten_date_now () ; 
 double emscripten_performance_now () ; 
 int performanceNow ; 

void test(void *userData)
{
	double now2 = emscripten_performance_now();
	assert(now2 >= performanceNow + 100);

	double now3 = emscripten_date_now();
	assert(now3 >= dateNow + 100);

#ifdef REPORT_RESULT
	REPORT_RESULT(0);
#endif
}