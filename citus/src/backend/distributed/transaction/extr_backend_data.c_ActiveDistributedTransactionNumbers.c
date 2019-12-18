#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_11__ {TYPE_2__* allProcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  transactionNumber; int /*<<< orphan*/  transactionOriginator; } ;
struct TYPE_10__ {TYPE_1__ transactionId; } ;
struct TYPE_9__ {scalar_t__ pid; } ;
typedef  TYPE_2__ PGPROC ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ BackendData ;

/* Variables and functions */
 int /*<<< orphan*/  GetBackendDataForProc (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  IsInDistributedTransaction (TYPE_3__*) ; 
 int MaxBackends ; 
 int /*<<< orphan*/ * NIL ; 
 TYPE_4__* ProcGlobal ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 

List *
ActiveDistributedTransactionNumbers(void)
{
	List *activeTransactionNumberList = NIL;
	int curBackend = 0;

	/* build list of starting procs */
	for (curBackend = 0; curBackend < MaxBackends; curBackend++)
	{
		PGPROC *currentProc = &ProcGlobal->allProcs[curBackend];
		BackendData currentBackendData;
		uint64 *transactionNumber = NULL;

		if (currentProc->pid == 0)
		{
			/* unused PGPROC slot */
			continue;
		}

		GetBackendDataForProc(currentProc, &currentBackendData);

		if (!IsInDistributedTransaction(&currentBackendData))
		{
			/* not a distributed transaction */
			continue;
		}

		if (!currentBackendData.transactionId.transactionOriginator)
		{
			/* not a coordinator process */
			continue;
		}

		transactionNumber = (uint64 *) palloc0(sizeof(uint64));
		*transactionNumber = currentBackendData.transactionId.transactionNumber;

		activeTransactionNumberList = lappend(activeTransactionNumberList,
											  transactionNumber);
	}

	return activeTransactionNumberList;
}