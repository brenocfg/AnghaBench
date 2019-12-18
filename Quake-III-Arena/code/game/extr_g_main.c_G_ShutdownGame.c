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
struct TYPE_2__ {scalar_t__ logFile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAIShutdown (int) ; 
 int /*<<< orphan*/  G_LogPrintf (char*) ; 
 int /*<<< orphan*/  G_Printf (char*) ; 
 int /*<<< orphan*/  G_WriteSessionData () ; 
 TYPE_1__ level ; 
 scalar_t__ trap_Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  trap_FS_FCloseFile (scalar_t__) ; 

void G_ShutdownGame( int restart ) {
	G_Printf ("==== ShutdownGame ====\n");

	if ( level.logFile ) {
		G_LogPrintf("ShutdownGame:\n" );
		G_LogPrintf("------------------------------------------------------------\n" );
		trap_FS_FCloseFile( level.logFile );
	}

	// write all the client session data so we can get it back
	G_WriteSessionData();

	if ( trap_Cvar_VariableIntegerValue( "bot_enable" ) ) {
		BotAIShutdown( restart );
	}
}