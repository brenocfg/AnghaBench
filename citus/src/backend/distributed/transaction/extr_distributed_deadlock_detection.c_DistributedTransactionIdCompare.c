#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ transactionNumber; scalar_t__ initiatorNodeIdentifier; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__ DistributedTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  TimestampDifferenceExceeds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
DistributedTransactionIdCompare(const void *a, const void *b, Size keysize)
{
	DistributedTransactionId *xactIdA = (DistributedTransactionId *) a;
	DistributedTransactionId *xactIdB = (DistributedTransactionId *) b;

	if (!TimestampDifferenceExceeds(xactIdB->timestamp, xactIdA->timestamp, 0))
	{
		/* ! (B <= A) = A < B */
		return -1;
	}
	else if (!TimestampDifferenceExceeds(xactIdA->timestamp, xactIdB->timestamp, 0))
	{
		/* ! (A <= B) = A > B */
		return 1;
	}
	else if (xactIdA->transactionNumber < xactIdB->transactionNumber)
	{
		return -1;
	}
	else if (xactIdA->transactionNumber > xactIdB->transactionNumber)
	{
		return 1;
	}
	else if (xactIdA->initiatorNodeIdentifier < xactIdB->initiatorNodeIdentifier)
	{
		return -1;
	}
	else if (xactIdA->initiatorNodeIdentifier > xactIdB->initiatorNodeIdentifier)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}