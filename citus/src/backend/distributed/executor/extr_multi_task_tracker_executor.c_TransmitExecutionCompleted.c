#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ TransmitExecStatus ;
struct TYPE_3__ {scalar_t__ nodeCount; scalar_t__* transmitStatusArray; } ;
typedef  TYPE_1__ TaskExecution ;

/* Variables and functions */
 scalar_t__ EXEC_TRANSMIT_DONE ; 

__attribute__((used)) static bool
TransmitExecutionCompleted(TaskExecution *taskExecution)
{
	bool completed = false;
	uint32 nodeIndex = 0;

	for (nodeIndex = 0; nodeIndex < taskExecution->nodeCount; nodeIndex++)
	{
		TransmitExecStatus *transmitStatusArray = taskExecution->transmitStatusArray;

		TransmitExecStatus transmitStatus = transmitStatusArray[nodeIndex];
		if (transmitStatus == EXEC_TRANSMIT_DONE)
		{
			completed = true;
			break;
		}
	}

	return completed;
}