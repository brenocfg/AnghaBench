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
 int /*<<< orphan*/  M_ReadSaveStrings () ; 
 int /*<<< orphan*/  M_SetupNextMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_StartMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SAVEDEAD ; 
 int /*<<< orphan*/  SaveDef ; 
 scalar_t__ gamestate ; 
 int /*<<< orphan*/  usergame ; 

void M_SaveGame (int choice)
{
    if (!usergame)
    {
	M_StartMessage(SAVEDEAD,NULL,false);
	return;
    }
	
    if (gamestate != GS_LEVEL)
	return;
	
    M_SetupNextMenu(&SaveDef);
    M_ReadSaveStrings();
}