#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32 ;
typedef  int TransactionId ;
typedef  int /*<<< orphan*/  Task ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int GetMyProcLocalTransactionId () ; 
 int /*<<< orphan*/ * LeftRotateList (int /*<<< orphan*/ *,int) ; 
 int list_length (int /*<<< orphan*/ *) ; 

List *
RoundRobinReorder(Task *task, List *placementList)
{
	TransactionId transactionId = GetMyProcLocalTransactionId();
	uint32 activePlacementCount = list_length(placementList);
	uint32 roundRobinIndex = (transactionId % activePlacementCount);

	placementList = LeftRotateList(placementList, roundRobinIndex);

	return placementList;
}