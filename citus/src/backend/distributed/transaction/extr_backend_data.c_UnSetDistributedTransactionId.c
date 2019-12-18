#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int initiatorNodeIdentifier; int transactionOriginator; } ;
struct TYPE_4__ {int transactionOriginator; scalar_t__ timestamp; scalar_t__ transactionNumber; scalar_t__ initiatorNodeIdentifier; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_2__ citusBackend; TYPE_1__ transactionId; scalar_t__ userId; scalar_t__ databaseId; } ;

/* Variables and functions */
 TYPE_3__* MyBackendData ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 

void
UnSetDistributedTransactionId(void)
{
	/* backend does not exist if the extension is not created */
	if (MyBackendData)
	{
		SpinLockAcquire(&MyBackendData->mutex);

		MyBackendData->databaseId = 0;
		MyBackendData->userId = 0;
		MyBackendData->transactionId.initiatorNodeIdentifier = 0;
		MyBackendData->transactionId.transactionOriginator = false;
		MyBackendData->transactionId.transactionNumber = 0;
		MyBackendData->transactionId.timestamp = 0;

		MyBackendData->citusBackend.initiatorNodeIdentifier = -1;
		MyBackendData->citusBackend.transactionOriginator = false;

		SpinLockRelease(&MyBackendData->mutex);
	}
}