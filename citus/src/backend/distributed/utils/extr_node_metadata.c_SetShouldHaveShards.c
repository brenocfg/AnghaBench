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
typedef  int /*<<< orphan*/  WorkerNode ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_dist_node_shouldhaveshards ; 
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/ * SetWorkerColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WorkerNode *
SetShouldHaveShards(WorkerNode *workerNode, bool shouldHaveShards)
{
	return SetWorkerColumn(workerNode, Anum_pg_dist_node_shouldhaveshards,
						   BoolGetDatum(shouldHaveShards));
}