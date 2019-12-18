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
typedef  int /*<<< orphan*/  WaitGraph ;
struct TYPE_3__ {int /*<<< orphan*/  isBlockingXactWaiting; void* blockingTransactionStamp; void* blockingTransactionNum; void* blockingNodeId; void* blockingPid; void* waitingTransactionStamp; void* waitingTransactionNum; void* waitingNodeId; void* waitingPid; } ;
typedef  TYPE_1__ WaitEdge ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 TYPE_1__* AllocWaitEdge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseBoolField (int /*<<< orphan*/ *,int,int) ; 
 void* ParseIntField (int /*<<< orphan*/ *,int,int) ; 
 void* ParseTimestampTzField (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
AddWaitEdgeFromResult(WaitGraph *waitGraph, PGresult *result, int rowIndex)
{
	WaitEdge *waitEdge = AllocWaitEdge(waitGraph);

	waitEdge->waitingPid = ParseIntField(result, rowIndex, 0);
	waitEdge->waitingNodeId = ParseIntField(result, rowIndex, 1);
	waitEdge->waitingTransactionNum = ParseIntField(result, rowIndex, 2);
	waitEdge->waitingTransactionStamp = ParseTimestampTzField(result, rowIndex, 3);
	waitEdge->blockingPid = ParseIntField(result, rowIndex, 4);
	waitEdge->blockingNodeId = ParseIntField(result, rowIndex, 5);
	waitEdge->blockingTransactionNum = ParseIntField(result, rowIndex, 6);
	waitEdge->blockingTransactionStamp = ParseTimestampTzField(result, rowIndex, 7);
	waitEdge->isBlockingXactWaiting = ParseBoolField(result, rowIndex, 8);
}