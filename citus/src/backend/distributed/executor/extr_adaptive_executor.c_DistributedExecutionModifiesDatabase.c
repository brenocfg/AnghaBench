#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tasksToExecute; int /*<<< orphan*/  modLevel; } ;
typedef  TYPE_1__ DistributedExecution ;

/* Variables and functions */
 int TaskListModifiesDatabase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
DistributedExecutionModifiesDatabase(DistributedExecution *execution)
{
	return TaskListModifiesDatabase(execution->modLevel, execution->tasksToExecute);
}