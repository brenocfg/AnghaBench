#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_11__ {char* workerName; int workerPort; int /*<<< orphan*/  groupId; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_13__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pgConn; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_2__ MultiConnection ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__* HeapTuple ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_INITSIZE ; 
 int /*<<< orphan*/  ALLOCSET_DEFAULT_MAXSIZE ; 
 int /*<<< orphan*/  ALLOCSET_DEFAULT_MINSIZE ; 
 int /*<<< orphan*/ * ActiveDistributedTransactionNumbers () ; 
 int /*<<< orphan*/ * AllocSetContextCreateExtended (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Anum_pg_dist_transaction_gid ; 
 int /*<<< orphan*/  Anum_pg_dist_transaction_groupid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DistTransactionGroupIndexId () ; 
 int /*<<< orphan*/  DistTransactionRelationId () ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 TYPE_2__* GetNodeConnection (int,char*,int) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ HeapTupleIsValid (TYPE_3__*) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int IsTransactionInProgress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ListToHashSet (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PendingWorkerTransactionList (TYPE_2__*) ; 
 int RecoverPreparedTransactionOnWorker (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int) ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_heap_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 TYPE_3__* systable_getnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
RecoverWorkerTransactions(WorkerNode *workerNode)
{
	int recoveredTransactionCount = 0;

	int32 groupId = workerNode->groupId;
	char *nodeName = workerNode->workerName;
	int nodePort = workerNode->workerPort;

	List *activeTransactionNumberList = NIL;
	HTAB *activeTransactionNumberSet = NULL;

	List *pendingTransactionList = NIL;
	HTAB *pendingTransactionSet = NULL;
	List *recheckTransactionList = NIL;
	HTAB *recheckTransactionSet = NULL;

	Relation pgDistTransaction = NULL;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[1];
	int scanKeyCount = 1;
	bool indexOK = true;
	HeapTuple heapTuple = NULL;
	TupleDesc tupleDescriptor = NULL;

	HASH_SEQ_STATUS status;

	MemoryContext localContext = NULL;
	MemoryContext oldContext = NULL;
	bool recoveryFailed = false;

	int connectionFlags = 0;
	MultiConnection *connection = GetNodeConnection(connectionFlags, nodeName, nodePort);
	if (connection->pgConn == NULL || PQstatus(connection->pgConn) != CONNECTION_OK)
	{
		ereport(WARNING, (errmsg("transaction recovery cannot connect to %s:%d",
								 nodeName, nodePort)));

		return 0;
	}

	localContext = AllocSetContextCreateExtended(CurrentMemoryContext,
												 "RecoverWorkerTransactions",
												 ALLOCSET_DEFAULT_MINSIZE,
												 ALLOCSET_DEFAULT_INITSIZE,
												 ALLOCSET_DEFAULT_MAXSIZE);

	oldContext = MemoryContextSwitchTo(localContext);

	/* take table lock first to avoid running concurrently */
	pgDistTransaction = heap_open(DistTransactionRelationId(), ShareUpdateExclusiveLock);
	tupleDescriptor = RelationGetDescr(pgDistTransaction);

	/*
	 * We're going to check the list of prepared transactions on the worker,
	 * but some of those prepared transactions might belong to ongoing
	 * distributed transactions.
	 *
	 * We could avoid this by temporarily blocking new prepared transactions
	 * from being created by taking an ExlusiveLock on pg_dist_transaction.
	 * However, this hurts write performance, so instead we avoid blocking
	 * by consulting the list of active distributed transactions, and follow
	 * a carefully chosen order to avoid race conditions:
	 *
	 * 1) P = prepared transactions on worker
	 * 2) A = active distributed transactions
	 * 3) T = pg_dist_transaction snapshot
	 * 4) Q = prepared transactions on worker
	 *
	 * By observing A after P, we get a conclusive answer to which distributed
	 * transactions we observed in P are still in progress. It is safe to recover
	 * the transactions in P - A based on the presence or absence of a record
	 * in T.
	 *
	 * We also remove records in T if there is no prepared transaction, which
	 * we assume means the transaction committed. However, a transaction could
	 * have left prepared transactions and committed between steps 1 and 2.
	 * In that case, we would incorrectly remove the records, while the
	 * prepared transaction is still in place.
	 *
	 * We therefore observe the set of prepared transactions one more time in
	 * step 4. The aforementioned transactions would show up in Q, but not in
	 * P. We can skip those transactions and recover them later.
	 */

	/* find stale prepared transactions on the remote node */
	pendingTransactionList = PendingWorkerTransactionList(connection);
	pendingTransactionSet = ListToHashSet(pendingTransactionList, NAMEDATALEN, true);

	/* find in-progress distributed transactions */
	activeTransactionNumberList = ActiveDistributedTransactionNumbers();
	activeTransactionNumberSet = ListToHashSet(activeTransactionNumberList,
											   sizeof(uint64), false);

	/* scan through all recovery records of the current worker */
	ScanKeyInit(&scanKey[0], Anum_pg_dist_transaction_groupid,
				BTEqualStrategyNumber, F_INT4EQ, Int32GetDatum(groupId));

	/* get a snapshot of pg_dist_transaction */
	scanDescriptor = systable_beginscan(pgDistTransaction,
										DistTransactionGroupIndexId(), indexOK,
										NULL, scanKeyCount, scanKey);

	/* find stale prepared transactions on the remote node */
	recheckTransactionList = PendingWorkerTransactionList(connection);
	recheckTransactionSet = ListToHashSet(recheckTransactionList, NAMEDATALEN, true);

	while (HeapTupleIsValid(heapTuple = systable_getnext(scanDescriptor)))
	{
		bool isNull = false;
		bool isTransactionInProgress = false;
		bool foundPreparedTransactionBeforeCommit = false;
		bool foundPreparedTransactionAfterCommit = false;

		Datum transactionNameDatum = heap_getattr(heapTuple,
												  Anum_pg_dist_transaction_gid,
												  tupleDescriptor, &isNull);
		char *transactionName = TextDatumGetCString(transactionNameDatum);

		isTransactionInProgress = IsTransactionInProgress(activeTransactionNumberSet,
														  transactionName);
		if (isTransactionInProgress)
		{
			/*
			 * Do not touch in progress transactions as we might mistakenly
			 * commit a transaction that is actually in the process of
			 * aborting or vice-versa.
			 */
			continue;
		}

		/*
		 * Remove the transaction from the pending list such that only transactions
		 * that need to be aborted remain at the end.
		 */
		hash_search(pendingTransactionSet, transactionName, HASH_REMOVE,
					&foundPreparedTransactionBeforeCommit);

		hash_search(recheckTransactionSet, transactionName, HASH_FIND,
					&foundPreparedTransactionAfterCommit);

		if (foundPreparedTransactionBeforeCommit && foundPreparedTransactionAfterCommit)
		{
			/*
			 * The transaction was committed, but the prepared transaction still exists
			 * on the worker. Try committing it.
			 *
			 * We double check that the recovery record exists both before and after
			 * checking ActiveDistributedTransactionNumbers(), since we may have
			 * observed a prepared transaction that was committed immediately after.
			 */
			bool shouldCommit = true;
			bool commitSucceeded = RecoverPreparedTransactionOnWorker(connection,
																	  transactionName,
																	  shouldCommit);
			if (!commitSucceeded)
			{
				/*
				 * Failed to commit on the current worker. Stop without throwing
				 * an error to allow recover_prepared_transactions to continue with
				 * other workers.
				 */
				recoveryFailed = true;
				break;
			}

			recoveredTransactionCount++;

			/*
			 * We successfully committed the prepared transaction, safe to delete
			 * the recovery record.
			 */
		}
		else if (foundPreparedTransactionAfterCommit)
		{
			/*
			 * We found a committed pg_dist_transaction record that initially did
			 * not have a prepared transaction, but did when we checked again.
			 *
			 * If a transaction started and committed just after we observed the
			 * set of prepared transactions, and just before we called
			 * ActiveDistributedTransactionNumbers, then we would see  a recovery
			 * record without a prepared transaction in pendingTransactionSet,
			 * but there may be prepared transactions that failed to commit.
			 * We should not delete the records for those prepared transactions,
			 * since we would otherwise roll back them on the next call to
			 * recover_prepared_transactions.
			 *
			 * In addition, if the transaction started after the call to
			 * ActiveDistributedTransactionNumbers and finished just before our
			 * pg_dist_transaction snapshot, then it may still be in the process
			 * of comitting the prepared transactions in the post-commit callback
			 * and we should not touch the prepared transactions.
			 *
			 * To handle these cases, we just leave the records and prepared
			 * transactions for the next call to recover_prepared_transactions
			 * and skip them here.
			 */

			continue;
		}
		else
		{
			/*
			 * We found a recovery record without any prepared transaction. It
			 * must have already been committed, so it's safe to delete the
			 * recovery record.
			 *
			 * Transactions that started after we observed pendingTransactionSet,
			 * but successfully committed their prepared transactions before
			 * ActiveDistributedTransactionNumbers are indistinguishable from
			 * transactions that committed at an earlier time, in which case it's
			 * safe delete the recovery record as well.
			 */
		}

		simple_heap_delete(pgDistTransaction, &heapTuple->t_self);
	}

	systable_endscan(scanDescriptor);
	heap_close(pgDistTransaction, NoLock);

	if (!recoveryFailed)
	{
		char *pendingTransactionName = NULL;
		bool abortSucceeded = true;

		/*
		 * All remaining prepared transactions that are not part of an in-progress
		 * distributed transaction should be aborted since we did not find a recovery
		 * record, which implies the disributed transaction aborted.
		 */
		hash_seq_init(&status, pendingTransactionSet);

		while ((pendingTransactionName = hash_seq_search(&status)) != NULL)
		{
			bool isTransactionInProgress = false;
			bool shouldCommit = false;

			isTransactionInProgress = IsTransactionInProgress(activeTransactionNumberSet,
															  pendingTransactionName);
			if (isTransactionInProgress)
			{
				continue;
			}

			shouldCommit = false;
			abortSucceeded = RecoverPreparedTransactionOnWorker(connection,
																pendingTransactionName,
																shouldCommit);
			if (!abortSucceeded)
			{
				hash_seq_term(&status);
				break;
			}

			recoveredTransactionCount++;
		}
	}

	MemoryContextSwitchTo(oldContext);
	MemoryContextDelete(localContext);

	return recoveredTransactionCount;
}