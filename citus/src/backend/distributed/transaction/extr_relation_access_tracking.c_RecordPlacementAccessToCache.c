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
typedef  TYPE_1__ RelationAccessHashKey ;
typedef  TYPE_2__ RelationAccessHashEntry ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  RelationAccessHash ; 
 TYPE_2__* hash_search (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
RecordPlacementAccessToCache(Oid relationId, ShardPlacementAccessType accessType)
{
	RelationAccessHashKey hashKey;
	RelationAccessHashEntry *hashEntry;
	bool found = false;

	hashKey.relationId = relationId;

	hashEntry = hash_search(RelationAccessHash, &hashKey, HASH_ENTER, &found);
	if (!found)
	{
		hashEntry->relationAccessMode = 0;
	}

	/* set the bit representing the access type */
	hashEntry->relationAccessMode |= (1 << (accessType));
}