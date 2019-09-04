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
 int /*<<< orphan*/  emscripten_set_timeout (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  func1Executed ; 
 int /*<<< orphan*/  func2 ; 

void func1(void *userData)
{
	assert((int)userData == 1);
	++func1Executed;

#ifdef REPORT_RESULT
	assert(func1Executed == 1);
#endif

	emscripten_set_timeout(func2, 100, (void*)2);
}