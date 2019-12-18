#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* widthInChars; } ;

/* Variables and functions */
 int COMMAND_HISTORY ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Con_Clear_f ; 
 int /*<<< orphan*/  Con_Dump_f ; 
 int /*<<< orphan*/  Con_MessageMode2_f ; 
 int /*<<< orphan*/  Con_MessageMode3_f ; 
 int /*<<< orphan*/  Con_MessageMode4_f ; 
 int /*<<< orphan*/  Con_MessageMode_f ; 
 int /*<<< orphan*/  Con_ToggleConsole_f ; 
 void* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Field_Clear (TYPE_1__*) ; 
 void* con_conspeed ; 
 void* con_notifytime ; 
 TYPE_1__ g_consoleField ; 
 void* g_console_field_width ; 
 TYPE_1__* historyEditLines ; 

void Con_Init (void) {
	int		i;

	con_notifytime = Cvar_Get ("con_notifytime", "3", 0);
	con_conspeed = Cvar_Get ("scr_conspeed", "3", 0);

	Field_Clear( &g_consoleField );
	g_consoleField.widthInChars = g_console_field_width;
	for ( i = 0 ; i < COMMAND_HISTORY ; i++ ) {
		Field_Clear( &historyEditLines[i] );
		historyEditLines[i].widthInChars = g_console_field_width;
	}

	Cmd_AddCommand ("toggleconsole", Con_ToggleConsole_f);
	Cmd_AddCommand ("messagemode", Con_MessageMode_f);
	Cmd_AddCommand ("messagemode2", Con_MessageMode2_f);
	Cmd_AddCommand ("messagemode3", Con_MessageMode3_f);
	Cmd_AddCommand ("messagemode4", Con_MessageMode4_f);
	Cmd_AddCommand ("clear", Con_Clear_f);
	Cmd_AddCommand ("condump", Con_Dump_f);
}