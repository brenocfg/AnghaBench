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
typedef  scalar_t__ int64 ;
struct TYPE_2__ {scalar_t__ relationId; scalar_t__ shardId; } ;
typedef  TYPE_1__ RelationShard ;
typedef  scalar_t__ Oid ;

/* Variables and functions */

int
CompareRelationShards(const void *leftElement, const void *rightElement)
{
	RelationShard *leftRelationShard = *((RelationShard **) leftElement);
	RelationShard *rightRelationShard = *((RelationShard **) rightElement);
	Oid leftRelationId = leftRelationShard->relationId;
	Oid rightRelationId = rightRelationShard->relationId;
	int64 leftShardId = leftRelationShard->shardId;
	int64 rightShardId = rightRelationShard->shardId;

	if (leftRelationId > rightRelationId)
	{
		return 1;
	}
	else if (leftRelationId < rightRelationId)
	{
		return -1;
	}
	else if (leftShardId > rightShardId)
	{
		return 1;
	}
	else if (leftShardId < rightShardId)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}