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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  TUBE ;

/* Variables and functions */
 int /*<<< orphan*/  SleepThread (scalar_t__) ; 
 int /*<<< orphan*/  UnixWaitForTubes (int /*<<< orphan*/ **,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Win32WaitForTubes (int /*<<< orphan*/ **,scalar_t__,scalar_t__) ; 

void WaitForTubes(TUBE **tubes, UINT num, UINT timeout)
{
	// Validate arguments
	if (num != 0 && tubes == NULL)
	{
		return;
	}
	if (timeout == 0)
	{
		return;
	}
	if (num == 0)
	{
		SleepThread(timeout);
		return;
	}

#ifdef	OS_WIN32
	Win32WaitForTubes(tubes, num, timeout);
#else	// OS_WIN32
	UnixWaitForTubes(tubes, num, timeout);
#endif	// OS_WIN32
}