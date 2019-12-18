#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * shardIntervalCompareFunction; } ;
struct TYPE_6__ {scalar_t__ maxValueExists; scalar_t__ minValueExists; int /*<<< orphan*/  maxValue; int /*<<< orphan*/  minValue; int /*<<< orphan*/  relationId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  TYPE_2__ DistTableCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CompareCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 

bool
ShardIntervalsOverlap(ShardInterval *firstInterval, ShardInterval *secondInterval)
{
	bool nonOverlap = false;
	DistTableCacheEntry *intervalRelation =
		DistributedTableCacheEntry(firstInterval->relationId);
	FmgrInfo *comparisonFunction = intervalRelation->shardIntervalCompareFunction;

	Datum firstMin = 0;
	Datum firstMax = 0;
	Datum secondMin = 0;
	Datum secondMax = 0;


	firstMin = firstInterval->minValue;
	firstMax = firstInterval->maxValue;
	secondMin = secondInterval->minValue;
	secondMax = secondInterval->maxValue;

	/*
	 * We need to have min/max values for both intervals first. Then, we assume
	 * two intervals i1 = [min1, max1] and i2 = [min2, max2] do not overlap if
	 * (max1 < min2) or (max2 < min1). For details, please see the explanation
	 * on overlapping intervals at http://www.rgrjr.com/emacs/overlap.html.
	 */
	if (firstInterval->minValueExists && firstInterval->maxValueExists &&
		secondInterval->minValueExists && secondInterval->maxValueExists)
	{
		Datum firstDatum = CompareCall2(comparisonFunction, firstMax, secondMin);
		Datum secondDatum = CompareCall2(comparisonFunction, secondMax, firstMin);
		int firstComparison = DatumGetInt32(firstDatum);
		int secondComparison = DatumGetInt32(secondDatum);

		if (firstComparison < 0 || secondComparison < 0)
		{
			nonOverlap = true;
		}
	}

	return (!nonOverlap);
}