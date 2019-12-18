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
 int /*<<< orphan*/  BotDefaultCharacteristics (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BotLoadCachedCharacter (char*,float,int /*<<< orphan*/ ) ; 
 char* DEFAULT_CHARACTER ; 
 int /*<<< orphan*/  LibVarGetValue (char*) ; 
 int /*<<< orphan*/ * botcharacters ; 
 int /*<<< orphan*/  qfalse ; 

int BotLoadCharacterSkill(char *charfile, float skill)
{
	int ch, defaultch;

	defaultch = BotLoadCachedCharacter(DEFAULT_CHARACTER, skill, qfalse);
	ch = BotLoadCachedCharacter(charfile, skill, LibVarGetValue("bot_reloadcharacters"));

	if (defaultch && ch)
	{
		BotDefaultCharacteristics(botcharacters[ch], botcharacters[defaultch]);
	} //end if

	return ch;
}