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
 int /*<<< orphan*/  emscripten_request_animation_frame (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  func1Executed ; 
 int /*<<< orphan*/  func2 ; 

EM_BOOL func1(double time, void *userData)
{
	assert((int)userData == 1);
	assert(time > 0);
	++func1Executed;

#ifdef REPORT_RESULT
	assert(func1Executed == 1);
#endif

	emscripten_request_animation_frame(func2, (void*)2);

	return 0;
}