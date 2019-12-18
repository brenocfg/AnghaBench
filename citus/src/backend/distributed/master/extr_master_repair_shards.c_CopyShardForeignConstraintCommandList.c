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
typedef  int /*<<< orphan*/  ShardInterval ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  CopyShardForeignConstraintCommandListGrouped (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
CopyShardForeignConstraintCommandList(ShardInterval *shardInterval)
{
	List *colocatedShardForeignConstraintCommandList = NIL;
	List *referenceTableForeignConstraintList = NIL;

	CopyShardForeignConstraintCommandListGrouped(shardInterval,
												 &
												 colocatedShardForeignConstraintCommandList,
												 &referenceTableForeignConstraintList);

	return list_concat(colocatedShardForeignConstraintCommandList,
					   referenceTableForeignConstraintList);
}