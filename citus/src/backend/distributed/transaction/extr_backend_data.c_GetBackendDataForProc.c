#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* backends; } ;
struct TYPE_11__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_10__ {int pgprocno; TYPE_1__* lockGroupLeader; } ;
struct TYPE_9__ {int pgprocno; } ;
typedef  TYPE_2__ PGPROC ;
typedef  TYPE_3__ BackendData ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_6__* backendManagementShmemData ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

void
GetBackendDataForProc(PGPROC *proc, BackendData *result)
{
	BackendData *backendData = NULL;
	int pgprocno = proc->pgprocno;

	if (proc->lockGroupLeader != NULL)
	{
		pgprocno = proc->lockGroupLeader->pgprocno;
	}

	backendData = &backendManagementShmemData->backends[pgprocno];

	SpinLockAcquire(&backendData->mutex);

	memcpy(result, backendData, sizeof(BackendData));

	SpinLockRelease(&backendData->mutex);
}