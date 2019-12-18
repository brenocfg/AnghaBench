#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mydest; int /*<<< orphan*/  rDestroy; int /*<<< orphan*/  rShutdown; int /*<<< orphan*/  rStartup; int /*<<< orphan*/  receiveSlot; } ;
struct TYPE_5__ {int partitionColumnIndex; int stopOnFailure; char* intermediateResultIdPrefix; int /*<<< orphan*/  memoryContext; int /*<<< orphan*/ * executorState; int /*<<< orphan*/ * columnNameList; int /*<<< orphan*/  distributedRelationId; TYPE_1__ pub; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  EState ;
typedef  TYPE_2__ CitusCopyDestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  CitusCopyDestReceiverDestroy ; 
 int /*<<< orphan*/  CitusCopyDestReceiverReceive ; 
 int /*<<< orphan*/  CitusCopyDestReceiverShutdown ; 
 int /*<<< orphan*/  CitusCopyDestReceiverStartup ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DestCopyOut ; 
 scalar_t__ palloc0 (int) ; 

CitusCopyDestReceiver *
CreateCitusCopyDestReceiver(Oid tableId, List *columnNameList, int partitionColumnIndex,
							EState *executorState, bool stopOnFailure,
							char *intermediateResultIdPrefix)
{
	CitusCopyDestReceiver *copyDest = NULL;

	copyDest = (CitusCopyDestReceiver *) palloc0(sizeof(CitusCopyDestReceiver));

	/* set up the DestReceiver function pointers */
	copyDest->pub.receiveSlot = CitusCopyDestReceiverReceive;
	copyDest->pub.rStartup = CitusCopyDestReceiverStartup;
	copyDest->pub.rShutdown = CitusCopyDestReceiverShutdown;
	copyDest->pub.rDestroy = CitusCopyDestReceiverDestroy;
	copyDest->pub.mydest = DestCopyOut;

	/* set up output parameters */
	copyDest->distributedRelationId = tableId;
	copyDest->columnNameList = columnNameList;
	copyDest->partitionColumnIndex = partitionColumnIndex;
	copyDest->executorState = executorState;
	copyDest->stopOnFailure = stopOnFailure;
	copyDest->intermediateResultIdPrefix = intermediateResultIdPrefix;
	copyDest->memoryContext = CurrentMemoryContext;

	return copyDest;
}