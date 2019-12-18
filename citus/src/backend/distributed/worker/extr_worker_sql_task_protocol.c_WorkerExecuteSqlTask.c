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
typedef  long int64 ;
struct TYPE_3__ {int /*<<< orphan*/  (* rDestroy ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {long tuplesSent; TYPE_1__ pub; } ;
typedef  TYPE_2__ TaskFileDestReceiver ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/ * ParamListInfo ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateExecutorState () ; 
 scalar_t__ CreateTaskFileDestReceiver (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExecuteQueryIntoDestReceiver (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

int64
WorkerExecuteSqlTask(Query *query, char *taskFilename, bool binaryCopyFormat)
{
	EState *estate = NULL;
	TaskFileDestReceiver *taskFileDest = NULL;
	ParamListInfo paramListInfo = NULL;
	int64 tuplesSent = 0L;

	estate = CreateExecutorState();
	taskFileDest =
		(TaskFileDestReceiver *) CreateTaskFileDestReceiver(taskFilename, estate,
															binaryCopyFormat);

	ExecuteQueryIntoDestReceiver(query, paramListInfo, (DestReceiver *) taskFileDest);

	tuplesSent = taskFileDest->tuplesSent;

	taskFileDest->pub.rDestroy((DestReceiver *) taskFileDest);
	FreeExecutorState(estate);

	return tuplesSent;
}