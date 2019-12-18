#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {int /*<<< orphan*/  filePath; int /*<<< orphan*/  fileCompat; int /*<<< orphan*/  columnOutputFunctions; TYPE_2__* copyOutState; int /*<<< orphan*/  executorState; scalar_t__ binaryCopyFormat; int /*<<< orphan*/  tupleDescriptor; int /*<<< orphan*/  memoryContext; } ;
typedef  TYPE_1__ TaskFileDestReceiver ;
struct TYPE_6__ {char* delim; char* null_print; char* null_print_client; int /*<<< orphan*/  fe_msgbuf; scalar_t__ binary; int /*<<< orphan*/  rowcontext; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  CopyOutStateData ;
typedef  TYPE_2__* CopyOutState ;

/* Variables and functions */
 int /*<<< orphan*/  AppendCopyBinaryHeaders (TYPE_2__*) ; 
 int /*<<< orphan*/  ColumnOutputFunctions (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FileCompatFromFileStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileOpenForTransmit (int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  GetPerTupleMemoryContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PG_BINARY ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  WriteToLocalFile (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  makeStringInfo () ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
TaskFileDestReceiverStartup(DestReceiver *dest, int operation,
							TupleDesc inputTupleDescriptor)
{
	TaskFileDestReceiver *taskFileDest = (TaskFileDestReceiver *) dest;

	CopyOutState copyOutState = NULL;
	const char *delimiterCharacter = "\t";
	const char *nullPrintCharacter = "\\N";

	const int fileFlags = (O_APPEND | O_CREAT | O_RDWR | O_TRUNC | PG_BINARY);
	const int fileMode = (S_IRUSR | S_IWUSR);

	/* use the memory context that was in place when the DestReceiver was created */
	MemoryContext oldContext = MemoryContextSwitchTo(taskFileDest->memoryContext);

	taskFileDest->tupleDescriptor = inputTupleDescriptor;

	/* define how tuples will be serialised */
	copyOutState = (CopyOutState) palloc0(sizeof(CopyOutStateData));
	copyOutState->delim = (char *) delimiterCharacter;
	copyOutState->null_print = (char *) nullPrintCharacter;
	copyOutState->null_print_client = (char *) nullPrintCharacter;
	copyOutState->binary = taskFileDest->binaryCopyFormat;
	copyOutState->fe_msgbuf = makeStringInfo();
	copyOutState->rowcontext = GetPerTupleMemoryContext(taskFileDest->executorState);
	taskFileDest->copyOutState = copyOutState;

	taskFileDest->columnOutputFunctions = ColumnOutputFunctions(inputTupleDescriptor,
																copyOutState->binary);

	taskFileDest->fileCompat = FileCompatFromFileStart(FileOpenForTransmit(
														   taskFileDest->filePath,
														   fileFlags,
														   fileMode));

	if (copyOutState->binary)
	{
		/* write headers when using binary encoding */
		resetStringInfo(copyOutState->fe_msgbuf);
		AppendCopyBinaryHeaders(copyOutState);

		WriteToLocalFile(copyOutState->fe_msgbuf, taskFileDest);
	}

	MemoryContextSwitchTo(oldContext);
}