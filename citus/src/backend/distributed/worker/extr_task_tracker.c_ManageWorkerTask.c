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
typedef  void* int32 ;
struct TYPE_3__ {int taskStatus; void* connectionId; scalar_t__ failureCount; int /*<<< orphan*/  taskId; int /*<<< orphan*/  taskCallString; int /*<<< orphan*/  userName; int /*<<< orphan*/  databaseName; int /*<<< orphan*/  jobId; } ;
typedef  TYPE_1__ WorkerTask ;
typedef  int /*<<< orphan*/  ResultStatus ;
typedef  int QueryStatus ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int CLIENT_QUERY_DONE ; 
 int CLIENT_QUERY_FAILED ; 
 int /*<<< orphan*/  CLIENT_RESULT_BUSY ; 
 int /*<<< orphan*/  CLIENT_RESULT_READY ; 
 int /*<<< orphan*/  CLIENT_RESULT_UNAVAILABLE ; 
 void* ConnectToLocalBackend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateJobDirectoryIfNotExists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FATAL ; 
 void* INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  JOB_CLEANUP_TASK_ID ; 
 scalar_t__ MAX_TASK_FAILURE_COUNT ; 
 int /*<<< orphan*/  MultiClientCancel (void*) ; 
 int /*<<< orphan*/  MultiClientDisconnect (void*) ; 
 int MultiClientQueryStatus (void*) ; 
 int /*<<< orphan*/  MultiClientResultStatus (void*) ; 
 int MultiClientSendQuery (void*,int /*<<< orphan*/ ) ; 
#define  TASK_ASSIGNED 136 
#define  TASK_CANCELED 135 
#define  TASK_CANCEL_REQUESTED 134 
#define  TASK_FAILED 133 
#define  TASK_PERMANENTLY_FAILED 132 
#define  TASK_RUNNING 131 
#define  TASK_SCHEDULED 130 
#define  TASK_SUCCEEDED 129 
#define  TASK_TO_REMOVE 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 

__attribute__((used)) static void
ManageWorkerTask(WorkerTask *workerTask, HTAB *WorkerTasksHash)
{
	switch (workerTask->taskStatus)
	{
		case TASK_ASSIGNED:
		{
			break;  /* nothing to do until the task gets scheduled */
		}

		case TASK_SCHEDULED:
		{
			/* create the job output directory if it does not exist */
			CreateJobDirectoryIfNotExists(workerTask->jobId);

			/* the task is ready to run; connect to local backend */
			workerTask->connectionId = ConnectToLocalBackend(workerTask->databaseName,
															 workerTask->userName);

			if (workerTask->connectionId != INVALID_CONNECTION_ID)
			{
				bool taskSent = MultiClientSendQuery(workerTask->connectionId,
													 workerTask->taskCallString);
				if (taskSent)
				{
					workerTask->taskStatus = TASK_RUNNING;
				}
				else
				{
					workerTask->taskStatus = TASK_FAILED;
					workerTask->failureCount++;

					MultiClientDisconnect(workerTask->connectionId);
					workerTask->connectionId = INVALID_CONNECTION_ID;
				}
			}
			else
			{
				workerTask->taskStatus = TASK_FAILED;
				workerTask->failureCount++;
			}

			break;
		}

		case TASK_RUNNING:
		{
			int32 connectionId = workerTask->connectionId;
			ResultStatus resultStatus = MultiClientResultStatus(connectionId);

			/* check if query results are ready, in progress, or unavailable */
			if (resultStatus == CLIENT_RESULT_READY)
			{
				QueryStatus queryStatus = MultiClientQueryStatus(connectionId);
				if (queryStatus == CLIENT_QUERY_DONE)
				{
					workerTask->taskStatus = TASK_SUCCEEDED;
				}
				else if (queryStatus == CLIENT_QUERY_FAILED)
				{
					workerTask->taskStatus = TASK_FAILED;
					workerTask->failureCount++;
				}
				else
				{
					ereport(FATAL, (errmsg("invalid query status: %d", queryStatus)));
				}
			}
			else if (resultStatus == CLIENT_RESULT_BUSY)
			{
				workerTask->taskStatus = TASK_RUNNING;
			}
			else if (resultStatus == CLIENT_RESULT_UNAVAILABLE)
			{
				workerTask->taskStatus = TASK_FAILED;
				workerTask->failureCount++;
			}

			/* clean up the connection if we are done with the task */
			if (resultStatus != CLIENT_RESULT_BUSY)
			{
				MultiClientDisconnect(workerTask->connectionId);
				workerTask->connectionId = INVALID_CONNECTION_ID;
			}

			break;
		}

		case TASK_FAILED:
		{
			if (workerTask->failureCount < MAX_TASK_FAILURE_COUNT)
			{
				workerTask->taskStatus = TASK_ASSIGNED;
			}
			else
			{
				workerTask->taskStatus = TASK_PERMANENTLY_FAILED;
			}

			break;
		}

		case TASK_PERMANENTLY_FAILED:
		case TASK_SUCCEEDED:
		{
			break;
		}

		case TASK_CANCEL_REQUESTED:
		{
			/*
			 * If this task is responsible for cleaning up the shared hash, we
			 * give the task more time instead of canceling it. The reason this
			 * task is marked for cancellation is that its file descriptor needs
			 * to be reclaimed after the clean up completes.
			 */
			if (workerTask->taskId == JOB_CLEANUP_TASK_ID)
			{
				workerTask->taskStatus = TASK_CANCELED;
				break;
			}

			if (workerTask->connectionId != INVALID_CONNECTION_ID)
			{
				int32 connectionId = workerTask->connectionId;

				ResultStatus status = MultiClientResultStatus(connectionId);
				if (status == CLIENT_RESULT_BUSY)
				{
					MultiClientCancel(connectionId);
				}
			}

			/* give the backend some time to flush its response */
			workerTask->taskStatus = TASK_CANCELED;
			break;
		}

		case TASK_CANCELED:
		{
			if (workerTask->connectionId != INVALID_CONNECTION_ID)
			{
				MultiClientDisconnect(workerTask->connectionId);
				workerTask->connectionId = INVALID_CONNECTION_ID;
			}

			workerTask->taskStatus = TASK_TO_REMOVE;
			break;
		}

		case TASK_TO_REMOVE:
		default:
		{
			/* we fatal here to avoid leaking client-side resources */
			ereport(FATAL, (errmsg("invalid task status: %d", workerTask->taskStatus)));
			break;
		}
	}

	Assert(workerTask->failureCount <= MAX_TASK_FAILURE_COUNT);
}