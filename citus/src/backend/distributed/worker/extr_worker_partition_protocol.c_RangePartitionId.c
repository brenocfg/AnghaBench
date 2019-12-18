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
typedef  int uint32 ;
typedef  int int32 ;
struct TYPE_2__ {int splitPointCount; int /*<<< orphan*/ * splitPointArray; int /*<<< orphan*/ * comparisonFunction; } ;
typedef  TYPE_1__ RangePartitionContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CompareCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
RangePartitionId(Datum partitionValue, const void *context)
{
	RangePartitionContext *rangePartitionContext = (RangePartitionContext *) context;
	FmgrInfo *comparisonFunction = rangePartitionContext->comparisonFunction;
	Datum *pointArray = rangePartitionContext->splitPointArray;
	int32 currentLength = rangePartitionContext->splitPointCount;
	int32 halfLength = 0;
	uint32 firstIndex = 0;

	/*
	 * We implement a binary search variant known as upper_bound. This variant
	 * gives us the semantics we need for partitioned joins; and is also used by
	 * Hadoop's TotalOrderPartitioner. To implement this variant, we rely on SGI
	 * STL v3.3's source code for upper_bound(). Note that elements in the point
	 * array cannot be null.
	 */
	while (currentLength > 0)
	{
		uint32 middleIndex = 0;
		Datum middlePoint = 0;
		Datum comparisonDatum = 0;
		int comparisonResult = 0;

		halfLength = currentLength >> 1;
		middleIndex = firstIndex;
		middleIndex += halfLength;

		middlePoint = pointArray[middleIndex];

		comparisonDatum = CompareCall2(comparisonFunction, partitionValue, middlePoint);
		comparisonResult = DatumGetInt32(comparisonDatum);

		/* if partition value is less than middle point */
		if (comparisonResult < 0)
		{
			currentLength = halfLength;
		}
		else
		{
			firstIndex = middleIndex;
			firstIndex++;
			currentLength = currentLength - halfLength - 1;
		}
	}

	return firstIndex;
}