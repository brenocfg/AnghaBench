#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,float,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BotDumpCharacter (int /*<<< orphan*/ ) ; 
 int BotFindCachedCharacter (char*,float) ; 
 int BotInterpolateCharacters (int,int,float) ; 
 int BotLoadCharacterSkill (char*,int) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/ * botcharacters ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,float,char*) ; 

int BotLoadCharacter(char *charfile, float skill)
{
	int firstskill, secondskill, handle;

	//make sure the skill is in the valid range
	if (skill < 1.0) skill = 1.0;
	else if (skill > 5.0) skill = 5.0;
	//skill 1, 4 and 5 should be available in the character files
	if (skill == 1.0 || skill == 4.0 || skill == 5.0)
	{
		return BotLoadCharacterSkill(charfile, skill);
	} //end if
	//check if there's a cached skill
	handle = BotFindCachedCharacter(charfile, skill);
	if (handle)
	{
		botimport.Print(PRT_MESSAGE, "loaded cached skill %f from %s\n", skill, charfile);
		return handle;
	} //end if
	if (skill < 4.0)
	{
		//load skill 1 and 4
		firstskill = BotLoadCharacterSkill(charfile, 1);
		if (!firstskill) return 0;
		secondskill = BotLoadCharacterSkill(charfile, 4);
		if (!secondskill) return firstskill;
	} //end if
	else
	{
		//load skill 4 and 5
		firstskill = BotLoadCharacterSkill(charfile, 4);
		if (!firstskill) return 0;
		secondskill = BotLoadCharacterSkill(charfile, 5);
		if (!secondskill) return firstskill;
	} //end else
	//interpolate between the two skills
	handle = BotInterpolateCharacters(firstskill, secondskill, skill);
	if (!handle) return 0;
	//write the character to the log file
	BotDumpCharacter(botcharacters[handle]);
	//
	return handle;
}