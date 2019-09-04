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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  QueueBudgetLock; scalar_t__ QueueBudget; } ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void CedarAddQueueBudget(CEDAR *c, int diff)
{
	// Validate arguments
	if (c == NULL || diff == 0)
	{
		return;
	}

	Lock(c->QueueBudgetLock);
	{
		int v = (int)c->QueueBudget;
		v += diff;
		c->QueueBudget = (UINT)v;
	}
	Unlock(c->QueueBudgetLock);
}