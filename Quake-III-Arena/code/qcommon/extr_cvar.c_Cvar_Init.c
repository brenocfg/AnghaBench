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
 int CVAR_ROM ; 
 int CVAR_SYSTEMINFO ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_Get (char*,char*,int) ; 
 int /*<<< orphan*/  Cvar_List_f ; 
 int /*<<< orphan*/  Cvar_Reset_f ; 
 int /*<<< orphan*/  Cvar_Restart_f ; 
 int /*<<< orphan*/  Cvar_SetA_f ; 
 int /*<<< orphan*/  Cvar_SetS_f ; 
 int /*<<< orphan*/  Cvar_SetU_f ; 
 int /*<<< orphan*/  Cvar_Set_f ; 
 int /*<<< orphan*/  Cvar_Toggle_f ; 
 int /*<<< orphan*/  cvar_cheats ; 

void Cvar_Init (void) {
	cvar_cheats = Cvar_Get("sv_cheats", "1", CVAR_ROM | CVAR_SYSTEMINFO );

	Cmd_AddCommand ("toggle", Cvar_Toggle_f);
	Cmd_AddCommand ("set", Cvar_Set_f);
	Cmd_AddCommand ("sets", Cvar_SetS_f);
	Cmd_AddCommand ("setu", Cvar_SetU_f);
	Cmd_AddCommand ("seta", Cvar_SetA_f);
	Cmd_AddCommand ("reset", Cvar_Reset_f);
	Cmd_AddCommand ("cvarlist", Cvar_List_f);
	Cmd_AddCommand ("cvar_restart", Cvar_Restart_f);
}