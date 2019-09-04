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
 double emscripten_get_now () ; 
 int /*<<< orphan*/  emscripten_thread_sleep (double) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

void Sleep(double msecs)
{
	double t1 = emscripten_get_now();
	emscripten_thread_sleep(msecs);
	double t2 = emscripten_get_now();
	printf("emscripten_thread_sleep() slept for %f msecs.\n", t2 - t1);

	assert(t2 - t1 >= 0.9 * msecs); // Should have slept ~ the requested time.
}