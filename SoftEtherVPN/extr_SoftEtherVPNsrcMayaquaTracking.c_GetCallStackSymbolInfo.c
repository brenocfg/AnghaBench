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
 int OSGetCallStackSymbolInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_lock ; 

bool GetCallStackSymbolInfo(CALLSTACK_DATA *s)
{
	bool ret;
	// Validate arguments
	if (s == NULL)
	{
		return false;
	}

	OSLock(cs_lock);
	{
		ret = OSGetCallStackSymbolInfo(s);
	}
	OSUnlock(cs_lock);

	return ret;
}