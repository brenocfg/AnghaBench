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
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ *) ; 
 int MAX_CLIENTS ; 
 int /*<<< orphan*/ ** botmovestates ; 

void BotShutdownMoveAI(void)
{
	int i;

	for (i = 1; i <= MAX_CLIENTS; i++)
	{
		if (botmovestates[i])
		{
			FreeMemory(botmovestates[i]);
			botmovestates[i] = NULL;
		} //end if
	} //end for
}