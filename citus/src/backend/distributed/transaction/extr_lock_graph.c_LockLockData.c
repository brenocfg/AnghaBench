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
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  LockBackendSharedMemory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHashPartitionLockByIndex (int) ; 
 int NUM_LOCK_PARTITIONS ; 

__attribute__((used)) static void
LockLockData(void)
{
	int partitionNum = 0;

	LockBackendSharedMemory(LW_SHARED);

	for (partitionNum = 0; partitionNum < NUM_LOCK_PARTITIONS; partitionNum++)
	{
		LWLockAcquire(LockHashPartitionLockByIndex(partitionNum), LW_SHARED);
	}
}