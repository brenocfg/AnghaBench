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
 int /*<<< orphan*/  emscripten_clear_immediate (long) ; 
 long emscripten_set_immediate (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  emscripten_set_timeout (void (*) (void*),int,void*) ; 
 int /*<<< orphan*/  func1 ; 
 int func2Executed ; 

void func2(void *userData)
{
	assert((int)userData == 2);
	++func2Executed;

	if (func2Executed == 1)
	{
		// Test canceling a setImmediate: register a callback but then cancel it immediately
		long id = emscripten_set_immediate(func1, (void*)2);
		emscripten_clear_immediate(id);

		emscripten_set_timeout(func2, 100, (void*)2);
	}
	if (func2Executed == 2)
	{
#ifdef REPORT_RESULT
		assert(func1Executed == 1);
		REPORT_RESULT(0);
#endif
	}
}