#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ int64 ;
struct TYPE_13__ {TYPE_1__* currentTask; TYPE_3__* workerPool; TYPE_6__* connection; } ;
typedef  TYPE_2__ WorkerSession ;
struct TYPE_14__ {TYPE_8__* distributedExecution; } ;
typedef  TYPE_3__ WorkerPool ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  TYPE_4__* TupleDesc ;
struct TYPE_19__ {char** columnArray; scalar_t__ rowsProcessed; int /*<<< orphan*/ * tupleStore; int /*<<< orphan*/ * attributeInputMetadata; TYPE_4__* tupleDescriptor; TYPE_7__* executionStats; } ;
struct TYPE_18__ {int /*<<< orphan*/  totalIntermediateResultSize; } ;
struct TYPE_17__ {int /*<<< orphan*/  pgConn; } ;
struct TYPE_16__ {int /*<<< orphan*/  gotResults; } ;
struct TYPE_15__ {scalar_t__ natts; } ;
struct TYPE_12__ {TYPE_5__* shardCommandExecution; } ;
typedef  TYPE_5__ ShardCommandExecution ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_6__ MultiConnection ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  scalar_t__ ExecStatusType ;
typedef  TYPE_7__ DistributedExecutionStats ;
typedef  TYPE_8__ DistributedExecution ;
typedef  int /*<<< orphan*/  AttInMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_INITSIZE ; 
 int /*<<< orphan*/  ALLOCSET_DEFAULT_MAXSIZE ; 
 int /*<<< orphan*/  ALLOCSET_DEFAULT_MINSIZE ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * BuildTupleFromCStrings (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ CheckIfSizeLimitIsExceeded (TYPE_7__*) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ErrorSizeLimitIsExceeded () ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_SINGLE_TUPLE ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQcmdTuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ PQgetlength (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PQisBusy (int /*<<< orphan*/ ) ; 
 scalar_t__ PQnfields (int /*<<< orphan*/ *) ; 
 scalar_t__ PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportResultError (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SubPlanLevel ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scanint8 (char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ReceiveResults(WorkerSession *session, bool storeRows)
{
	bool fetchDone = false;
	MultiConnection *connection = session->connection;
	WorkerPool *workerPool = session->workerPool;
	DistributedExecution *execution = workerPool->distributedExecution;
	DistributedExecutionStats *executionStats = execution->executionStats;
	TupleDesc tupleDescriptor = execution->tupleDescriptor;
	AttInMetadata *attributeInputMetadata = execution->attributeInputMetadata;
	uint32 expectedColumnCount = 0;
	char **columnArray = execution->columnArray;
	Tuplestorestate *tupleStore = execution->tupleStore;
	MemoryContext ioContext = NULL;

	if (tupleDescriptor != NULL)
	{
		expectedColumnCount = tupleDescriptor->natts;
	}

	/*
	 * We use this context while converting each row fetched from remote node
	 * into tuple. The context is reseted on every row, thus we create it at the
	 * start of the loop and reset on every iteration.
	 */
	ioContext = AllocSetContextCreate(CurrentMemoryContext,
									  "IoContext",
									  ALLOCSET_DEFAULT_MINSIZE,
									  ALLOCSET_DEFAULT_INITSIZE,
									  ALLOCSET_DEFAULT_MAXSIZE);

	while (!PQisBusy(connection->pgConn))
	{
		uint32 rowIndex = 0;
		uint32 columnIndex = 0;
		uint32 rowsProcessed = 0;
		uint32 columnCount = 0;
		ExecStatusType resultStatus = 0;

		PGresult *result = PQgetResult(connection->pgConn);
		if (result == NULL)
		{
			/* no more results, break out of loop and free allocated memory */
			fetchDone = true;
			break;
		}

		resultStatus = PQresultStatus(result);
		if (resultStatus == PGRES_COMMAND_OK)
		{
			char *currentAffectedTupleString = PQcmdTuples(result);
			int64 currentAffectedTupleCount = 0;
			ShardCommandExecution *shardCommandExecution =
				session->currentTask->shardCommandExecution;

			/* if there are multiple replicas, make sure to consider only one */
			if (!shardCommandExecution->gotResults && *currentAffectedTupleString != '\0')
			{
				scanint8(currentAffectedTupleString, false, &currentAffectedTupleCount);
				Assert(currentAffectedTupleCount >= 0);

				execution->rowsProcessed += currentAffectedTupleCount;
			}

			PQclear(result);

			/* no more results, break out of loop and free allocated memory */
			fetchDone = true;
			break;
		}
		else if (resultStatus == PGRES_TUPLES_OK)
		{
			/*
			 * We've already consumed all the tuples, no more results. Break out
			 * of loop and free allocated memory before returning.
			 */
			Assert(PQntuples(result) == 0);
			PQclear(result);

			fetchDone = true;
			break;
		}
		else if (resultStatus != PGRES_SINGLE_TUPLE)
		{
			/* query failures are always hard errors */
			ReportResultError(connection, result, ERROR);
		}
		else if (!storeRows)
		{
			/*
			 * Already receieved rows from executing on another shard placement or
			 * doesn't need at all (e.g., DDL).
			 */
			PQclear(result);
			continue;
		}

		rowsProcessed = PQntuples(result);
		columnCount = PQnfields(result);

		if (columnCount != expectedColumnCount)
		{
			ereport(ERROR, (errmsg("unexpected number of columns from worker: %d, "
								   "expected %d",
								   columnCount, expectedColumnCount)));
		}

		for (rowIndex = 0; rowIndex < rowsProcessed; rowIndex++)
		{
			HeapTuple heapTuple = NULL;
			MemoryContext oldContextPerRow = NULL;
			memset(columnArray, 0, columnCount * sizeof(char *));

			for (columnIndex = 0; columnIndex < columnCount; columnIndex++)
			{
				if (PQgetisnull(result, rowIndex, columnIndex))
				{
					columnArray[columnIndex] = NULL;
				}
				else
				{
					columnArray[columnIndex] = PQgetvalue(result, rowIndex, columnIndex);
					if (SubPlanLevel > 0 && executionStats != NULL)
					{
						executionStats->totalIntermediateResultSize += PQgetlength(result,
																				   rowIndex,
																				   columnIndex);
					}
				}
			}

			/*
			 * Switch to a temporary memory context that we reset after each tuple. This
			 * protects us from any memory leaks that might be present in I/O functions
			 * called by BuildTupleFromCStrings.
			 */
			oldContextPerRow = MemoryContextSwitchTo(ioContext);

			heapTuple = BuildTupleFromCStrings(attributeInputMetadata, columnArray);

			MemoryContextSwitchTo(oldContextPerRow);

			tuplestore_puttuple(tupleStore, heapTuple);
			MemoryContextReset(ioContext);

			execution->rowsProcessed++;
		}

		PQclear(result);

		if (executionStats != NULL && CheckIfSizeLimitIsExceeded(executionStats))
		{
			ErrorSizeLimitIsExceeded();
		}
	}

	/* the context is local to the function, so not needed anymore */
	MemoryContextDelete(ioContext);

	return fetchDone;
}