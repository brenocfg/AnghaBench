#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ partitionMethod; } ;
struct TYPE_27__ {int /*<<< orphan*/  hasOverlappingShardInterval; TYPE_3__** sortedShardIntervalArray; } ;
struct TYPE_26__ {scalar_t__ lessEqualConsts; scalar_t__ lessConsts; scalar_t__ greaterEqualConsts; scalar_t__ greaterConsts; TYPE_2__* hashedEqualConsts; TYPE_1__* equalConsts; scalar_t__ evaluatesToFalse; } ;
struct TYPE_25__ {scalar_t__ shardId; } ;
struct TYPE_24__ {int /*<<< orphan*/  constvalue; } ;
struct TYPE_23__ {int /*<<< orphan*/  constvalue; } ;
typedef  TYPE_3__ ShardInterval ;
typedef  TYPE_4__ PruningInstance ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_5__ DistTableCacheEntry ;
typedef  TYPE_6__ ClauseWalkerContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DISTRIBUTE_BY_HASH ; 
 int /*<<< orphan*/ * ExhaustivePrune (TYPE_5__*,TYPE_6__*,TYPE_4__*) ; 
 scalar_t__ ExhaustivePruneOne (TYPE_3__*,TYPE_6__*,TYPE_4__*) ; 
 TYPE_3__* FindShardInterval (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int FindShardIntervalIndex (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int INVALID_SHARD_INDEX ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * PruneWithBoundaries (TYPE_5__*,TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_3__*) ; 

__attribute__((used)) static List *
PruneOne(DistTableCacheEntry *cacheEntry, ClauseWalkerContext *context,
		 PruningInstance *prune)
{
	ShardInterval *shardInterval = NULL;

	/* Well, if life always were this easy... */
	if (prune->evaluatesToFalse)
	{
		return NIL;
	}

	/*
	 * For an equal constraints, if there's no overlapping shards (always the
	 * case for hash and range partitioning, sometimes for append), can
	 * perform binary search for the right interval.  That's usually the
	 * fastest, so try that first.
	 */
	if (prune->equalConsts &&
		!cacheEntry->hasOverlappingShardInterval)
	{
		shardInterval = FindShardInterval(prune->equalConsts->constvalue, cacheEntry);

		/*
		 * If pruned down to nothing, we're done. Otherwise see if other
		 * methods prune down further / to nothing.
		 */
		if (!shardInterval)
		{
			return NIL;
		}
	}

	/*
	 * If the hash value we're looking for is known, we can search for the
	 * interval directly.  That's fast and should only ever be the case for a
	 * hash-partitioned table.
	 */
	if (prune->hashedEqualConsts)
	{
		int shardIndex = INVALID_SHARD_INDEX;
		ShardInterval **sortedShardIntervalArray = cacheEntry->sortedShardIntervalArray;

		Assert(context->partitionMethod == DISTRIBUTE_BY_HASH);

		shardIndex = FindShardIntervalIndex(prune->hashedEqualConsts->constvalue,
											cacheEntry);

		if (shardIndex == INVALID_SHARD_INDEX)
		{
			return NIL;
		}
		else if (shardInterval &&
				 sortedShardIntervalArray[shardIndex]->shardId != shardInterval->shardId)
		{
			/*
			 * equalConst based pruning above yielded a different shard than
			 * pruning based on pre-hashed equality.  This is useful in case
			 * of INSERT ... SELECT, where both can occur together (one via
			 * join/colocation, the other via a plain equality restriction).
			 */
			return NIL;
		}
		else
		{
			return list_make1(sortedShardIntervalArray[shardIndex]);
		}
	}

	/*
	 * If previous pruning method yielded a single shard, and the table is not
	 * hash partitioned, attempt range based pruning to exclude it further.
	 *
	 * That's particularly important in particular for subquery pushdown,
	 * where it's very common to have a user specified equality restriction,
	 * and a range based restriction for shard boundaries, added by the
	 * subquery machinery.
	 */
	if (shardInterval)
	{
		if (context->partitionMethod != DISTRIBUTE_BY_HASH &&
			ExhaustivePruneOne(shardInterval, context, prune))
		{
			return NIL;
		}
		else
		{
			/* no chance to prune further, return */
			return list_make1(shardInterval);
		}
	}

	/*
	 * Should never get here for hashing, we've filtered down to either zero
	 * or one shard, and returned.
	 */
	Assert(context->partitionMethod != DISTRIBUTE_BY_HASH);

	/*
	 * Next method: binary search with fuzzy boundaries. Can't trivially do so
	 * if shards have overlapping boundaries.
	 *
	 * TODO: If we kept shard intervals separately sorted by both upper and
	 * lower boundaries, this should be possible?
	 */
	if (!cacheEntry->hasOverlappingShardInterval && (
			prune->greaterConsts || prune->greaterEqualConsts ||
			prune->lessConsts || prune->lessEqualConsts))
	{
		return PruneWithBoundaries(cacheEntry, context, prune);
	}

	/*
	 * Brute force: Check each shard.
	 */
	return ExhaustivePrune(cacheEntry, context, prune);
}