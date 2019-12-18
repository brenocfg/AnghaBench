#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_5__ {scalar_t__ groupId; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/ * GetWorkerNodeHash () ; 
 scalar_t__ NodeIsPrimary (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_term (int /*<<< orphan*/ *) ; 

WorkerNode *
PrimaryNodeForGroup(int32 groupId, bool *groupContainsNodes)
{
	WorkerNode *workerNode = NULL;
	HASH_SEQ_STATUS status;
	HTAB *workerNodeHash = GetWorkerNodeHash();

	hash_seq_init(&status, workerNodeHash);

	while ((workerNode = hash_seq_search(&status)) != NULL)
	{
		int32 workerNodeGroupId = workerNode->groupId;
		if (workerNodeGroupId != groupId)
		{
			continue;
		}

		if (groupContainsNodes != NULL)
		{
			*groupContainsNodes = true;
		}

		if (NodeIsPrimary(workerNode))
		{
			hash_seq_term(&status);
			return workerNode;
		}
	}

	return NULL;
}