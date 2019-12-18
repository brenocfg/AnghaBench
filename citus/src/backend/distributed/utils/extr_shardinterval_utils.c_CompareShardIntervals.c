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
struct TYPE_2__ {int /*<<< orphan*/  minValue; int /*<<< orphan*/  maxValueExists; int /*<<< orphan*/  minValueExists; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CompareCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CompareShardIntervalsById (void const*,void const*) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 

int
CompareShardIntervals(const void *leftElement, const void *rightElement,
					  FmgrInfo *typeCompareFunction)
{
	ShardInterval *leftShardInterval = *((ShardInterval **) leftElement);
	ShardInterval *rightShardInterval = *((ShardInterval **) rightElement);
	int comparisonResult = 0;
	bool leftHasNull = (!leftShardInterval->minValueExists ||
						!leftShardInterval->maxValueExists);
	bool rightHasNull = (!rightShardInterval->minValueExists ||
						 !rightShardInterval->maxValueExists);

	Assert(typeCompareFunction != NULL);

	if (leftHasNull && rightHasNull)
	{
		comparisonResult = 0;
	}
	else if (leftHasNull)
	{
		comparisonResult = 1;
	}
	else if (rightHasNull)
	{
		comparisonResult = -1;
	}
	else
	{
		/* if both shard interval have min/max values, calculate comparison result */
		Datum leftDatum = leftShardInterval->minValue;
		Datum rightDatum = rightShardInterval->minValue;
		Datum comparisonDatum = CompareCall2(typeCompareFunction, leftDatum, rightDatum);
		comparisonResult = DatumGetInt32(comparisonDatum);
	}

	/* Two different shards should never be equal */
	if (comparisonResult == 0)
	{
		return CompareShardIntervalsById(leftElement, rightElement);
	}

	return comparisonResult;
}