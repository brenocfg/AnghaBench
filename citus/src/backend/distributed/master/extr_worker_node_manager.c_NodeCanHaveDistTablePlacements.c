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
struct TYPE_4__ {int shouldHaveShards; } ;
typedef  TYPE_1__ WorkerNode ;

/* Variables and functions */
 int /*<<< orphan*/  NodeIsPrimary (TYPE_1__*) ; 

__attribute__((used)) static bool
NodeCanHaveDistTablePlacements(WorkerNode *node)
{
	if (!NodeIsPrimary(node))
	{
		return false;
	}

	return node->shouldHaveShards;
}