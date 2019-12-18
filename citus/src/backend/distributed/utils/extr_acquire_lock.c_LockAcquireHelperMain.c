#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_10__ {scalar_t__ bgw_extra; } ;
struct TYPE_9__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
struct TYPE_8__ {int /*<<< orphan*/  DatabaseId; int /*<<< orphan*/  lock_cooldown; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ LockAcquireHelperArgs ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BackgroundWorkerInitializeConnectionByOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BackgroundWorkerUnblockSignals () ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 long DeadlineTimestampTzToTimeout (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LOG ; 
 TYPE_6__* MyBgworkerEntry ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int SPI_OK_SELECT ; 
 int /*<<< orphan*/  SPI_connect () ; 
 int SPI_execute_with_args (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_finish () ; 
 int /*<<< orphan*/  SPI_getbinval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int SPI_processed ; 
 TYPE_5__* SPI_tuptable ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  SetCurrentStatementStartTimestamp () ; 
 scalar_t__ ShouldAcquireLock (int) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  TimestampTzPlusMilliseconds (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  lock_acquire_helper_sigterm ; 
 int /*<<< orphan*/  pgstat_report_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgstat_report_stat (int) ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 

void
LockAcquireHelperMain(Datum main_arg)
{
	int backendPid = DatumGetInt32(main_arg);
	StringInfoData sql;
	LockAcquireHelperArgs *args = (LockAcquireHelperArgs *) MyBgworkerEntry->bgw_extra;
	long timeout = 0;
	const TimestampTz connectionStart = GetCurrentTimestamp();
	const TimestampTz deadline = TimestampTzPlusMilliseconds(connectionStart,
															 args->lock_cooldown);

	/* parameters for sql query to be executed */
	const int paramCount = 1;
	Oid paramTypes[1] = { INT4OID };
	Datum paramValues[1];

	pqsignal(SIGTERM, lock_acquire_helper_sigterm);

	BackgroundWorkerUnblockSignals();

	elog(LOG, "lock acquiring backend started for backend %d (cooldown %dms)", backendPid,
		 args->lock_cooldown);

	/*
	 * this loop waits till the deadline is reached (eg. lock_cooldown has passed) OR we
	 * no longer need to acquire the lock due to the termination of this backend.
	 * Only after the timeout the code will continue with the section that will acquire
	 * the lock.
	 */
	do {
		timeout = DeadlineTimestampTzToTimeout(deadline);
	} while (timeout > 0 && ShouldAcquireLock(timeout));

	/* connecting to the database */
	BackgroundWorkerInitializeConnectionByOid(args->DatabaseId, InvalidOid, 0);

	/*
	 * The query below does a self join on pg_locks to find backends that are granted a
	 * lock our target backend (backendPid) is waiting for. Once it found such a backend
	 * it terminates the backend with pg_terminate_pid.
	 *
	 * The result is are rows of pid,bool indicating backend that is terminated and the
	 * success of the termination. These will be logged accordingly below for an
	 * administrator to correlate in the logs with the termination message.
	 */
	initStringInfo(&sql);
	appendStringInfo(&sql,
					 "SELECT \n"
					 "    DISTINCT conflicting.pid,\n"
					 "    pg_terminate_backend(conflicting.pid)\n"
					 "  FROM pg_locks AS blocked\n"
					 "       JOIN pg_locks AS conflicting\n"
					 "         ON (conflicting.database = blocked.database\n"
					 "             AND conflicting.objid = blocked.objid)\n"
					 " WHERE conflicting.granted = true\n"
					 "   AND blocked.granted = false\n"
					 "   AND blocked.pid = $1;");
	paramValues[0] = Int32GetDatum(backendPid);

	while (ShouldAcquireLock(100))
	{
		int row = 0;
		int spiStatus = 0;

		elog(LOG, "canceling competing backends for backend %d", backendPid);

		/*
		 * Begin our transaction
		 */
		SetCurrentStatementStartTimestamp();
		StartTransactionCommand();
		SPI_connect();
		PushActiveSnapshot(GetTransactionSnapshot());
		pgstat_report_activity(STATE_RUNNING, sql.data);

		spiStatus = SPI_execute_with_args(sql.data, paramCount, paramTypes, paramValues,
										  NULL, false, 0);

		if (spiStatus == SPI_OK_SELECT)
		{
			for (row = 0; row < SPI_processed; row++)
			{
				int terminatedPid = 0;
				bool isTerminated = false;
				bool isnull = false;

				terminatedPid = DatumGetInt32(SPI_getbinval(SPI_tuptable->vals[0],
															SPI_tuptable->tupdesc,
															1, &isnull));

				isTerminated = DatumGetBool(SPI_getbinval(SPI_tuptable->vals[0],
														  SPI_tuptable->tupdesc,
														  2, &isnull));

				if (isTerminated)
				{
					elog(WARNING, "terminated conflicting backend %d", terminatedPid);
				}
				else
				{
					elog(INFO,
						 "attempt to terminate conflicting backend %d was unsuccessful",
						 terminatedPid);
				}
			}
		}
		else
		{
			elog(FATAL, "cannot cancel competing backends for backend %d", backendPid);
		}

		/*
		 * And finish our transaction.
		 */
		SPI_finish();
		PopActiveSnapshot();
		CommitTransactionCommand();
		pgstat_report_stat(false);
		pgstat_report_activity(STATE_IDLE, NULL);
	}


	elog(LOG, "lock acquiring backend finished for backend %d", backendPid);

	/* safely got to the end, exit without problem */
	proc_exit(0);
}