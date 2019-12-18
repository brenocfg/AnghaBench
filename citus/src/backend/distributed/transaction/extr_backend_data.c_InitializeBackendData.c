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
struct TYPE_4__ {size_t pgprocno; } ;
struct TYPE_3__ {int /*<<< orphan*/ * backends; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LockBackendSharedMemory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MyBackendData ; 
 TYPE_2__* MyProc ; 
 int /*<<< orphan*/  UnSetDistributedTransactionId () ; 
 int /*<<< orphan*/  UnlockBackendSharedMemory () ; 
 TYPE_1__* backendManagementShmemData ; 

void
InitializeBackendData(void)
{
	if (MyBackendData != NULL)
	{
		/*
		 * We already initialized MyBackendData before. We definitely should
		 * not initialise it again, because we might be in the middle of a
		 * distributed transaction.
		 */
		return;
	}

	MyBackendData = &backendManagementShmemData->backends[MyProc->pgprocno];

	Assert(MyBackendData);

	LockBackendSharedMemory(LW_EXCLUSIVE);

	/* zero out the backend data */
	UnSetDistributedTransactionId();

	UnlockBackendSharedMemory();
}