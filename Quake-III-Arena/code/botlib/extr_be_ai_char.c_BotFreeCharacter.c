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
 int /*<<< orphan*/  LibVarGetValue (char*) ; 

void BotFreeCharacter(int handle)
{
	if (!LibVarGetValue("bot_reloadcharacters")) return;
	BotFreeCharacter2(handle);
}