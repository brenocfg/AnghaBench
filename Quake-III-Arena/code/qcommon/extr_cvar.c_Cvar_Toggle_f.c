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
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_Set2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Cvar_VariableValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  va (char*,int) ; 

void Cvar_Toggle_f( void ) {
	int		v;

	if ( Cmd_Argc() != 2 ) {
		Com_Printf ("usage: toggle <variable>\n");
		return;
	}

	v = Cvar_VariableValue( Cmd_Argv( 1 ) );
	v = !v;

	Cvar_Set2 (Cmd_Argv(1), va("%i", v), qfalse);
}