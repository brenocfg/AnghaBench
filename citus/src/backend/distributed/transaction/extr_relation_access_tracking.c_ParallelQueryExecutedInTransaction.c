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
struct TYPE_2__ {int relationAccessMode; } ;
typedef  TYPE_1__ RelationAccessHashEntry ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int PARALLEL_ACCESS_MASK ; 
 int /*<<< orphan*/ * RelationAccessHash ; 
 int /*<<< orphan*/  ShouldRecordRelationAccess () ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_term (int /*<<< orphan*/ *) ; 

bool
ParallelQueryExecutedInTransaction(void)
{
	HASH_SEQ_STATUS status;
	RelationAccessHashEntry *hashEntry;

	if (!ShouldRecordRelationAccess() || RelationAccessHash == NULL)
	{
		return false;
	}

	hash_seq_init(&status, RelationAccessHash);

	hashEntry = (RelationAccessHashEntry *) hash_seq_search(&status);
	while (hashEntry != NULL)
	{
		int relationAccessMode = hashEntry->relationAccessMode;
		if ((relationAccessMode & PARALLEL_ACCESS_MASK))
		{
			hash_seq_term(&status);
			return true;
		}

		hashEntry = (RelationAccessHashEntry *) hash_seq_search(&status);
	}

	return false;
}