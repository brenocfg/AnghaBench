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
struct TYPE_4__ {char* resultId; int writeLocalFile; int /*<<< orphan*/  memoryContext; int /*<<< orphan*/ * initialNodeList; int /*<<< orphan*/ * executorState; TYPE_1__ pub; } ;
typedef  TYPE_2__ RemoteFileDestReceiver ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DestCopyOut ; 
 int /*<<< orphan*/  RemoteFileDestReceiverDestroy ; 
 int /*<<< orphan*/  RemoteFileDestReceiverReceive ; 
 int /*<<< orphan*/  RemoteFileDestReceiverShutdown ; 
 int /*<<< orphan*/  RemoteFileDestReceiverStartup ; 
 scalar_t__ palloc0 (int) ; 

DestReceiver *
CreateRemoteFileDestReceiver(char *resultId, EState *executorState,
							 List *initialNodeList, bool writeLocalFile)
{
	RemoteFileDestReceiver *resultDest = NULL;

	resultDest = (RemoteFileDestReceiver *) palloc0(sizeof(RemoteFileDestReceiver));

	/* set up the DestReceiver function pointers */
	resultDest->pub.receiveSlot = RemoteFileDestReceiverReceive;
	resultDest->pub.rStartup = RemoteFileDestReceiverStartup;
	resultDest->pub.rShutdown = RemoteFileDestReceiverShutdown;
	resultDest->pub.rDestroy = RemoteFileDestReceiverDestroy;
	resultDest->pub.mydest = DestCopyOut;

	/* set up output parameters */
	resultDest->resultId = resultId;
	resultDest->executorState = executorState;
	resultDest->initialNodeList = initialNodeList;
	resultDest->memoryContext = CurrentMemoryContext;
	resultDest->writeLocalFile = writeLocalFile;

	return (DestReceiver *) resultDest;
}