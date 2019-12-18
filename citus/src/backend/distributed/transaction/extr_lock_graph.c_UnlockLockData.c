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
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHashPartitionLockByIndex (int) ; 
 int NUM_LOCK_PARTITIONS ; 
 int /*<<< orphan*/  UnlockBackendSharedMemory () ; 

__attribute__((used)) static void
UnlockLockData(void)
{
	int partitionNum = 0;

	for (partitionNum = NUM_LOCK_PARTITIONS - 1; partitionNum >= 0; partitionNum--)
	{
		LWLockRelease(LockHashPartitionLockByIndex(partitionNum));
	}

	UnlockBackendSharedMemory();
}