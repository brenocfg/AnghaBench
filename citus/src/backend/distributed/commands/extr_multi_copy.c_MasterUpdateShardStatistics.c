#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;

/* Variables and functions */
 int /*<<< orphan*/  RemoteUpdateShardStatistics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateShardStatistics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * masterConnection ; 

__attribute__((used)) static void
MasterUpdateShardStatistics(uint64 shardId)
{
	if (masterConnection == NULL)
	{
		UpdateShardStatistics(shardId);
	}
	else
	{
		RemoteUpdateShardStatistics(shardId);
	}
}