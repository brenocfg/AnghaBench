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
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_cancel_animation_frame (long) ; 
 long emscripten_request_animation_frame (int /*<<< orphan*/  (*) (double,void*),void*) ; 
 int /*<<< orphan*/  func1 (double,void*) ; 
 int func2Executed ; 

EM_BOOL func2(double time, void *userData)
{
	assert((int)userData == 2);
	assert(time > 0);
	++func2Executed;

	if (func2Executed == 1)
	{
		// Test canceling an animation frame: register rAF() but then cancel it immediately
		long id = emscripten_request_animation_frame(func1, (void*)2);
		emscripten_cancel_animation_frame(id);

		emscripten_request_animation_frame(func2, (void*)2);
	}
	if (func2Executed == 2)
	{
#ifdef REPORT_RESULT
		assert(func1Executed == 1);
		REPORT_RESULT(0);
#endif
	}
	return 0;
}