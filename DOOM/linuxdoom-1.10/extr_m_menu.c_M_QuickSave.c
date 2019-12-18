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
 scalar_t__ GS_LEVEL ; 
 int /*<<< orphan*/  M_QuickSaveResponse ; 
 int /*<<< orphan*/  M_ReadSaveStrings () ; 
 int /*<<< orphan*/  M_SetupNextMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_StartControlPanel () ; 
 int /*<<< orphan*/  M_StartMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* QSPROMPT ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SaveDef ; 
 scalar_t__ gamestate ; 
 size_t quickSaveSlot ; 
 int /*<<< orphan*/ * savegamestrings ; 
 int /*<<< orphan*/  sfx_oof ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempstring ; 
 int /*<<< orphan*/  usergame ; 

void M_QuickSave(void)
{
    if (!usergame)
    {
	S_StartSound(NULL,sfx_oof);
	return;
    }

    if (gamestate != GS_LEVEL)
	return;
	
    if (quickSaveSlot < 0)
    {
	M_StartControlPanel();
	M_ReadSaveStrings();
	M_SetupNextMenu(&SaveDef);
	quickSaveSlot = -2;	// means to pick a slot now
	return;
    }
    sprintf(tempstring,QSPROMPT,savegamestrings[quickSaveSlot]);
    M_StartMessage(tempstring,M_QuickSaveResponse,true);
}