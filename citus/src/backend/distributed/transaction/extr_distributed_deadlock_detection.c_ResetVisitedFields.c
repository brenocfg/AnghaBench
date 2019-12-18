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
struct TYPE_2__ {int transactionVisited; } ;
typedef  TYPE_1__ TransactionNode ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ResetVisitedFields(HTAB *adjacencyList)
{
	HASH_SEQ_STATUS status;
	TransactionNode *resetNode = NULL;

	/* reset all visited fields */
	hash_seq_init(&status, adjacencyList);

	while ((resetNode = (TransactionNode *) hash_seq_search(&status)) != 0)
	{
		resetNode->transactionVisited = false;
	}
}