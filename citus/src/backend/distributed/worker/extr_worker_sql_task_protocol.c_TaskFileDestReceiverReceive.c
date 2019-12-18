#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* tts_isnull; int /*<<< orphan*/ * tts_values; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_9__ {int /*<<< orphan*/  tuplesSent; int /*<<< orphan*/ * executorState; int /*<<< orphan*/ * columnOutputFunctions; TYPE_3__* copyOutState; int /*<<< orphan*/  tupleDescriptor; } ;
typedef  TYPE_2__ TaskFileDestReceiver ;
struct TYPE_10__ {int /*<<< orphan*/  fe_msgbuf; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__* CopyOutState ;

/* Variables and functions */
 int /*<<< orphan*/  AppendCopyRowData (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetPerTupleMemoryContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetPerTupleExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteToLocalFile (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_1__*) ; 

__attribute__((used)) static bool
TaskFileDestReceiverReceive(TupleTableSlot *slot, DestReceiver *dest)
{
	TaskFileDestReceiver *taskFileDest = (TaskFileDestReceiver *) dest;

	TupleDesc tupleDescriptor = taskFileDest->tupleDescriptor;

	CopyOutState copyOutState = taskFileDest->copyOutState;
	FmgrInfo *columnOutputFunctions = taskFileDest->columnOutputFunctions;

	Datum *columnValues = NULL;
	bool *columnNulls = NULL;
	StringInfo copyData = copyOutState->fe_msgbuf;

	EState *executorState = taskFileDest->executorState;
	MemoryContext executorTupleContext = GetPerTupleMemoryContext(executorState);
	MemoryContext oldContext = MemoryContextSwitchTo(executorTupleContext);

	slot_getallattrs(slot);

	columnValues = slot->tts_values;
	columnNulls = slot->tts_isnull;

	resetStringInfo(copyData);

	/* construct row in COPY format */
	AppendCopyRowData(columnValues, columnNulls, tupleDescriptor,
					  copyOutState, columnOutputFunctions, NULL);

	WriteToLocalFile(copyOutState->fe_msgbuf, taskFileDest);

	MemoryContextSwitchTo(oldContext);

	taskFileDest->tuplesSent++;

	ResetPerTupleExprContext(executorState);

	return true;
}