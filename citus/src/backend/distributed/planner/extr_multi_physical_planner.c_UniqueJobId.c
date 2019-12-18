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
typedef  int uint64 ;
typedef  int uint32 ;

/* Variables and functions */
 scalar_t__ EnableUniqueJobIds ; 
 int GetLocalGroupId () ; 
 int MyProcPid ; 
 scalar_t__ RecoveryInProgress () ; 

uint64
UniqueJobId(void)
{
	static uint32 jobIdCounter = 0;

	uint64 jobId = 0;
	uint64 jobIdNumber = 0;
	uint64 processId = 0;
	uint64 localGroupId = 0;

	jobIdCounter++;

	if (EnableUniqueJobIds)
	{
		/*
		 * Add the local group id information to the jobId to
		 * prevent concurrent jobs on different groups to conflict.
		 */
		localGroupId = GetLocalGroupId() & 0xFF;
		jobId = jobId | (localGroupId << 48);

		/*
		 * Add the current process ID to distinguish jobs by this
		 * backends from jobs started by other backends. Process
		 * IDs can have at most 24-bits on platforms supported by
		 * Citus.
		 */
		processId = MyProcPid & 0xFFFFFF;
		jobId = jobId | (processId << 24);

		/*
		 * Add an extra bit for secondaries to distinguish their
		 * jobs from primaries.
		 */
		if (RecoveryInProgress())
		{
			jobId = jobId | (1 << 23);
		}
	}

	/*
	 * Use the remaining 23 bits to distinguish jobs by the
	 * same backend.
	 */
	jobIdNumber = jobIdCounter & 0x1FFFFFF;
	jobId = jobId | jobIdNumber;

	return jobId;
}