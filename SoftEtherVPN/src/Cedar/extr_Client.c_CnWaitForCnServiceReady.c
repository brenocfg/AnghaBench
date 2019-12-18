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
typedef  scalar_t__ UINT64 ;

/* Variables and functions */
 scalar_t__ CLIENT_WAIT_CN_READY_TIMEOUT ; 
 scalar_t__ CnIsCnServiceReady () ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 scalar_t__ Tick64 () ; 

void CnWaitForCnServiceReady()
{
	UINT64 start_time = Tick64();

	while ((start_time + (UINT64)CLIENT_WAIT_CN_READY_TIMEOUT) >= Tick64())
	{
		if (CnIsCnServiceReady())
		{
			break;
		}

		SleepThread(100);
	}
}