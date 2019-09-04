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
typedef  int /*<<< orphan*/  CALLSTACK_DATA ;

/* Variables and functions */
 int /*<<< orphan*/ * OSGetCallStack () ; 
 int /*<<< orphan*/  OSLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WalkDownCallStack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cs_lock ; 
 scalar_t__ do_not_get_callstack ; 

CALLSTACK_DATA *GetCallStack()
{
	CALLSTACK_DATA *s;
	if (do_not_get_callstack)
	{
		// Not to get the call stack
		return NULL;
	}

	OSLock(cs_lock);
	{
		// Get the call stack
		s = OSGetCallStack();
	}
	OSUnlock(cs_lock);
	if (s == NULL)
	{
		return NULL;
	}

	// Descend in the call stack for 3 steps
	s = WalkDownCallStack(s, 3);

	return s;
}