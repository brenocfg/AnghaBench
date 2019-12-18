#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  transactionNumber; int /*<<< orphan*/  transactionOriginator; int /*<<< orphan*/  initiatorNodeIdentifier; } ;
struct TYPE_8__ {TYPE_1__ transactionId; } ;
struct TYPE_7__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  transactionNumber; int /*<<< orphan*/  transactionOriginator; int /*<<< orphan*/  initiatorNodeIdentifier; } ;
typedef  TYPE_2__ DistributedTransactionId ;
typedef  TYPE_3__ BackendData ;

/* Variables and functions */
 int /*<<< orphan*/  GetBackendDataForProc (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  MyProc ; 
 scalar_t__ palloc (int) ; 

DistributedTransactionId *
GetCurrentDistributedTransactionId(void)
{
	DistributedTransactionId *currentDistributedTransactionId =
		(DistributedTransactionId *) palloc(sizeof(DistributedTransactionId));
	BackendData backendData;

	GetBackendDataForProc(MyProc, &backendData);

	currentDistributedTransactionId->initiatorNodeIdentifier =
		backendData.transactionId.initiatorNodeIdentifier;
	currentDistributedTransactionId->transactionOriginator =
		backendData.transactionId.transactionOriginator;
	currentDistributedTransactionId->transactionNumber =
		backendData.transactionId.transactionNumber;
	currentDistributedTransactionId->timestamp =
		backendData.transactionId.timestamp;

	return currentDistributedTransactionId;
}