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
typedef  int /*<<< orphan*/  DistributedExecution ;

/* Variables and functions */
 scalar_t__ DistributedExecutionModifiesDatabase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnsetCitusNoticeLevel () ; 
 int /*<<< orphan*/  XACT_MODIFICATION_DATA ; 
 int /*<<< orphan*/  XactModificationLevel ; 

__attribute__((used)) static void
FinishDistributedExecution(DistributedExecution *execution)
{
	UnsetCitusNoticeLevel();

	if (DistributedExecutionModifiesDatabase(execution))
	{
		/* prevent copying shards in same transaction */
		XactModificationLevel = XACT_MODIFICATION_DATA;
	}
}