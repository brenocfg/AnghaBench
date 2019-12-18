#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int relationAccessMode; } ;
struct TYPE_5__ {int /*<<< orphan*/  relationId; } ;
typedef  int ShardPlacementAccessType ;
typedef  int /*<<< orphan*/  RelationAccessMode ;
typedef  TYPE_1__ RelationAccessHashKey ;
typedef  TYPE_2__ RelationAccessHashEntry ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int PARALLEL_MODE_FLAG_OFFSET ; 
 int /*<<< orphan*/  RELATION_NOT_ACCESSED ; 
 int /*<<< orphan*/  RELATION_PARALLEL_ACCESSED ; 
 int /*<<< orphan*/  RELATION_REFERENCE_ACCESSED ; 
 int /*<<< orphan*/  RelationAccessHash ; 
 int /*<<< orphan*/  ShouldRecordRelationAccess () ; 
 TYPE_2__* hash_search (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static RelationAccessMode
GetRelationAccessMode(Oid relationId, ShardPlacementAccessType accessType)
{
	RelationAccessHashKey hashKey;
	RelationAccessHashEntry *hashEntry;
	int relationAcessMode = 0;
	bool found = false;
	int parallelRelationAccessBit = accessType + PARALLEL_MODE_FLAG_OFFSET;

	/* no point in getting the mode when not inside a transaction block */
	if (!ShouldRecordRelationAccess())
	{
		return RELATION_NOT_ACCESSED;
	}

	hashKey.relationId = relationId;

	hashEntry = hash_search(RelationAccessHash, &hashKey, HASH_FIND, &found);
	if (!found)
	{
		/* relation not accessed at all */
		return RELATION_NOT_ACCESSED;
	}


	relationAcessMode = hashEntry->relationAccessMode;
	if (!(relationAcessMode & (1 << accessType)))
	{
		/* relation not accessed with the given access type */
		return RELATION_NOT_ACCESSED;
	}

	if (relationAcessMode & (1 << parallelRelationAccessBit))
	{
		return RELATION_PARALLEL_ACCESSED;
	}
	else
	{
		return RELATION_REFERENCE_ACCESSED;
	}
}