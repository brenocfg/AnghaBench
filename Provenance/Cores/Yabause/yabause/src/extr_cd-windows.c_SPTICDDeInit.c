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
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int KillCDThread ; 
 int /*<<< orphan*/  TerminateThread (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_cs ; 
 scalar_t__ hCDROM ; 
 scalar_t__ thread_handle ; 

void SPTICDDeInit() {
	if (thread_handle != INVALID_HANDLE_VALUE)                               
	{
		// Set the flag telling it to stop
		KillCDThread=1;
		if (WaitForSingleObject(thread_handle,INFINITE) == WAIT_TIMEOUT)      
		{
			// Couldn't close thread cleanly
			TerminateThread(thread_handle,0);
		}
		CloseHandle(thread_handle);
		thread_handle = INVALID_HANDLE_VALUE;
	}
	DeleteCriticalSection(&cd_cs);

	CloseHandle(hCDROM);
}