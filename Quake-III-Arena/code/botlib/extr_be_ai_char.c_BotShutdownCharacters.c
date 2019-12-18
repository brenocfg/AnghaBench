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
 int /*<<< orphan*/  BotFreeCharacter2 (int) ; 
 int MAX_CLIENTS ; 
 scalar_t__* botcharacters ; 

void BotShutdownCharacters(void)
{
	int handle;

	for (handle = 1; handle <= MAX_CLIENTS; handle++)
	{
		if (botcharacters[handle])
		{
			BotFreeCharacter2(handle);
		} //end if
	} //end for
}