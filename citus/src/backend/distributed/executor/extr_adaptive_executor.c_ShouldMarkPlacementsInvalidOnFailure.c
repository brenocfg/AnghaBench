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
struct TYPE_4__ {scalar_t__ errorOnAnyFailure; } ;
typedef  TYPE_1__ DistributedExecution ;

/* Variables and functions */
 int /*<<< orphan*/  DistributedExecutionModifiesDatabase (TYPE_1__*) ; 

__attribute__((used)) static bool
ShouldMarkPlacementsInvalidOnFailure(DistributedExecution *execution)
{
	if (!DistributedExecutionModifiesDatabase(execution) || execution->errorOnAnyFailure)
	{
		/*
		 * Failures that do not modify the database (e.g., mainly SELECTs) should
		 * never lead to invalid placement.
		 *
		 * Failures that lead throwing error, no need to mark any placement
		 * invalid.
		 */
		return false;
	}

	return true;
}