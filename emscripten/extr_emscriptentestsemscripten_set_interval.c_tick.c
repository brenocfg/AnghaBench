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
 int /*<<< orphan*/  emscripten_clear_interval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_timeout (int /*<<< orphan*/ ,int,void*) ; 
 int funcExecuted ; 
 int /*<<< orphan*/  intervalId ; 
 int /*<<< orphan*/  testDone ; 

void tick(void *userData)
{
	assert((int)userData == 1);
	++funcExecuted;
	if (funcExecuted == 10)
	{
		emscripten_set_timeout(testDone, 300, (void*)2);
	}
	if (funcExecuted >= 10)
	{
		emscripten_clear_interval(intervalId);
	}
}