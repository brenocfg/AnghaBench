#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mydest; int /*<<< orphan*/  rDestroy; int /*<<< orphan*/  rShutdown; int /*<<< orphan*/  rStartup; int /*<<< orphan*/  receiveSlot; } ;
struct TYPE_4__ {int binaryCopyFormat; int /*<<< orphan*/  filePath; int /*<<< orphan*/  memoryContext; int /*<<< orphan*/ * executorState; TYPE_1__ pub; } ;
typedef  TYPE_2__ TaskFileDestReceiver ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DestCopyOut ; 
 int /*<<< orphan*/  TaskFileDestReceiverDestroy ; 
 int /*<<< orphan*/  TaskFileDestReceiverReceive ; 
 int /*<<< orphan*/  TaskFileDestReceiverShutdown ; 
 int /*<<< orphan*/  TaskFileDestReceiverStartup ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 

__attribute__((used)) static DestReceiver *
CreateTaskFileDestReceiver(char *filePath, EState *executorState, bool binaryCopyFormat)
{
	TaskFileDestReceiver *taskFileDest = NULL;

	taskFileDest = (TaskFileDestReceiver *) palloc0(sizeof(TaskFileDestReceiver));

	/* set up the DestReceiver function pointers */
	taskFileDest->pub.receiveSlot = TaskFileDestReceiverReceive;
	taskFileDest->pub.rStartup = TaskFileDestReceiverStartup;
	taskFileDest->pub.rShutdown = TaskFileDestReceiverShutdown;
	taskFileDest->pub.rDestroy = TaskFileDestReceiverDestroy;
	taskFileDest->pub.mydest = DestCopyOut;

	/* set up output parameters */
	taskFileDest->executorState = executorState;
	taskFileDest->memoryContext = CurrentMemoryContext;
	taskFileDest->filePath = pstrdup(filePath);
	taskFileDest->binaryCopyFormat = binaryCopyFormat;

	return (DestReceiver *) taskFileDest;
}