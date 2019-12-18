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
struct TYPE_3__ {struct TYPE_3__* filePath; struct TYPE_3__* columnOutputFunctions; struct TYPE_3__* copyOutState; } ;
typedef  TYPE_1__ TaskFileDestReceiver ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
TaskFileDestReceiverDestroy(DestReceiver *destReceiver)
{
	TaskFileDestReceiver *taskFileDest = (TaskFileDestReceiver *) destReceiver;

	if (taskFileDest->copyOutState)
	{
		pfree(taskFileDest->copyOutState);
	}

	if (taskFileDest->columnOutputFunctions)
	{
		pfree(taskFileDest->columnOutputFunctions);
	}

	pfree(taskFileDest->filePath);
	pfree(taskFileDest);
}