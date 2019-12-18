#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  valueTypeLen; int /*<<< orphan*/  valueByVal; void* maxValue; scalar_t__ maxValueExists; void* minValue; scalar_t__ minValueExists; int /*<<< orphan*/  shardIndex; int /*<<< orphan*/  shardId; int /*<<< orphan*/  valueTypeId; int /*<<< orphan*/  storageType; int /*<<< orphan*/  relationId; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ShardInterval ;

/* Variables and functions */
 void* datumCopy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
CopyShardInterval(ShardInterval *srcInterval, ShardInterval *destInterval)
{
	destInterval->type = srcInterval->type;
	destInterval->relationId = srcInterval->relationId;
	destInterval->storageType = srcInterval->storageType;
	destInterval->valueTypeId = srcInterval->valueTypeId;
	destInterval->valueTypeLen = srcInterval->valueTypeLen;
	destInterval->valueByVal = srcInterval->valueByVal;
	destInterval->minValueExists = srcInterval->minValueExists;
	destInterval->maxValueExists = srcInterval->maxValueExists;
	destInterval->shardId = srcInterval->shardId;
	destInterval->shardIndex = srcInterval->shardIndex;

	destInterval->minValue = 0;
	if (destInterval->minValueExists)
	{
		destInterval->minValue = datumCopy(srcInterval->minValue,
										   srcInterval->valueByVal,
										   srcInterval->valueTypeLen);
	}

	destInterval->maxValue = 0;
	if (destInterval->maxValueExists)
	{
		destInterval->maxValue = datumCopy(srcInterval->maxValue,
										   srcInterval->valueByVal,
										   srcInterval->valueTypeLen);
	}
}