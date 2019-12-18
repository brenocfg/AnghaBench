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
typedef  scalar_t__ uint64 ;
struct TYPE_2__ {scalar_t__ anchorShardId; } ;
typedef  TYPE_1__ Task ;

/* Variables and functions */

__attribute__((used)) static int
CompareTasksByShardId(const void *leftElement, const void *rightElement)
{
	const Task *leftTask = *((const Task **) leftElement);
	const Task *rightTask = *((const Task **) rightElement);

	uint64 leftShardId = leftTask->anchorShardId;
	uint64 rightShardId = rightTask->anchorShardId;

	/* we compare 64-bit integers, instead of casting their difference to int */
	if (leftShardId > rightShardId)
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