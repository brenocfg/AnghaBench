#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  pg_atomic_uint64 ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_6__ {int initiatorNodeIdentifier; int transactionOriginator; } ;
struct TYPE_5__ {int initiatorNodeIdentifier; int transactionOriginator; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  transactionNumber; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; TYPE_2__ citusBackend; TYPE_1__ transactionId; int /*<<< orphan*/  userId; int /*<<< orphan*/  databaseId; } ;
struct TYPE_7__ {int /*<<< orphan*/  nextTransactionNumber; } ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int GetLocalGroupId () ; 
 int /*<<< orphan*/  GetUserId () ; 
 TYPE_4__* MyBackendData ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_3__* backendManagementShmemData ; 
 int /*<<< orphan*/  pg_atomic_fetch_add_u64 (int /*<<< orphan*/ *,int) ; 

void
AssignDistributedTransactionId(void)
{
	pg_atomic_uint64 *transactionNumberSequence =
		&backendManagementShmemData->nextTransactionNumber;

	uint64 nextTransactionNumber = pg_atomic_fetch_add_u64(transactionNumberSequence, 1);
	int localGroupId = GetLocalGroupId();
	TimestampTz currentTimestamp = GetCurrentTimestamp();
	Oid userId = GetUserId();

	SpinLockAcquire(&MyBackendData->mutex);

	MyBackendData->databaseId = MyDatabaseId;
	MyBackendData->userId = userId;

	MyBackendData->transactionId.initiatorNodeIdentifier = localGroupId;
	MyBackendData->transactionId.transactionOriginator = true;
	MyBackendData->transactionId.transactionNumber = nextTransactionNumber;
	MyBackendData->transactionId.timestamp = currentTimestamp;

	MyBackendData->citusBackend.initiatorNodeIdentifier = localGroupId;
	MyBackendData->citusBackend.transactionOriginator = true;

	SpinLockRelease(&MyBackendData->mutex);
}