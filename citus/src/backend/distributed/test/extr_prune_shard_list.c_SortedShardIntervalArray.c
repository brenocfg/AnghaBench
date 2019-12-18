#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int shardIntervalArrayLength; TYPE_1__** sortedShardIntervalArray; } ;
struct TYPE_4__ {int /*<<< orphan*/  shardId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ DistTableCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumArrayToArrayType (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * palloc0 (int) ; 

__attribute__((used)) static ArrayType *
SortedShardIntervalArray(Oid distributedTableId)
{
	ArrayType *shardIdArrayType = NULL;
	int shardIndex = 0;
	Oid shardIdTypeId = INT8OID;

	DistTableCacheEntry *cacheEntry = DistributedTableCacheEntry(distributedTableId);
	ShardInterval **shardIntervalArray = cacheEntry->sortedShardIntervalArray;
	int shardIdCount = cacheEntry->shardIntervalArrayLength;
	Datum *shardIdDatumArray = palloc0(shardIdCount * sizeof(Datum));

	for (shardIndex = 0; shardIndex < shardIdCount; ++shardIndex)
	{
		ShardInterval *shardId = shardIntervalArray[shardIndex];
		Datum shardIdDatum = Int64GetDatum(shardId->shardId);

		shardIdDatumArray[shardIndex] = shardIdDatum;
	}

	shardIdArrayType = DatumArrayToArrayType(shardIdDatumArray, shardIdCount,
											 shardIdTypeId);

	return shardIdArrayType;
}