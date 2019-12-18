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

/* Variables and functions */
 int /*<<< orphan*/  BotFreeGoalState (int) ; 
 int /*<<< orphan*/  BotFreeInfoEntities () ; 
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ *) ; 
 int MAX_CLIENTS ; 
 scalar_t__* botgoalstates ; 
 int /*<<< orphan*/ * freelevelitems ; 
 int /*<<< orphan*/ * itemconfig ; 
 int /*<<< orphan*/ * levelitemheap ; 
 int /*<<< orphan*/ * levelitems ; 
 scalar_t__ numlevelitems ; 

void BotShutdownGoalAI(void)
{
	int i;

	if (itemconfig) FreeMemory(itemconfig);
	itemconfig = NULL;
	if (levelitemheap) FreeMemory(levelitemheap);
	levelitemheap = NULL;
	freelevelitems = NULL;
	levelitems = NULL;
	numlevelitems = 0;

	BotFreeInfoEntities();

	for (i = 1; i <= MAX_CLIENTS; i++)
	{
		if (botgoalstates[i])
		{
			BotFreeGoalState(i);
		} //end if
	} //end for
}