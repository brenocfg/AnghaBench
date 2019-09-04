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
typedef  scalar_t__ UINT64 ;
struct TYPE_3__ {int /*<<< orphan*/  TickList; } ;
typedef  TYPE_1__ INTERRUPT_MANAGER ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (scalar_t__*,int) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Search (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void AddInterrupt(INTERRUPT_MANAGER *m, UINT64 tick)
{
	// Validate arguments
	if (tick == 0)
	{
		return;
	}

	LockList(m->TickList);
	{
		if (Search(m->TickList, &tick) == NULL)
		{
			Insert(m->TickList, Clone(&tick, sizeof(UINT64)));
		}
	}
	UnlockList(m->TickList);
}