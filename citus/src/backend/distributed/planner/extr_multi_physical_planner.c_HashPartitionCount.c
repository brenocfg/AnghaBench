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
typedef  double uint32 ;

/* Variables and functions */
 double ActiveReadableWorkerNodeCount () ; 
 double MaxRunningTasksPerNode ; 
 int /*<<< orphan*/  rint (double) ; 

__attribute__((used)) static uint32
HashPartitionCount(void)
{
	uint32 groupCount = ActiveReadableWorkerNodeCount();
	double maxReduceTasksPerNode = MaxRunningTasksPerNode / 2.0;

	uint32 partitionCount = (uint32) rint(groupCount * maxReduceTasksPerNode);
	return partitionCount;
}