#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  port; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ netadr_t ;
struct TYPE_6__ {int masterNum; int nummplayerservers; int numglobalservers; int /*<<< orphan*/  pingUpdateSource; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_GLOBAL ; 
 int /*<<< orphan*/  AS_MPLAYER ; 
 int /*<<< orphan*/  BigShort (int /*<<< orphan*/ ) ; 
 int Cmd_Argc () ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 scalar_t__ Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  MASTER_SERVER_NAME ; 
 int /*<<< orphan*/  NA_IP ; 
 int /*<<< orphan*/  NET_OutOfBandPrint (int /*<<< orphan*/ ,TYPE_1__,char*) ; 
 int /*<<< orphan*/  NET_StringToAdr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NS_SERVER ; 
 int /*<<< orphan*/  PORT_MASTER ; 
 int atoi (char*) ; 
 TYPE_2__ cls ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char*) ; 

void CL_GlobalServers_f( void ) {
	netadr_t	to;
	int			i;
	int			count;
	char		*buffptr;
	char		command[1024];
	
	if ( Cmd_Argc() < 3) {
		Com_Printf( "usage: globalservers <master# 0-1> <protocol> [keywords]\n");
		return;	
	}

	cls.masterNum = atoi( Cmd_Argv(1) );

	Com_Printf( "Requesting servers from the master...\n");

	// reset the list, waiting for response
	// -1 is used to distinguish a "no response"

	if( cls.masterNum == 1 ) {
		NET_StringToAdr( MASTER_SERVER_NAME, &to );
		cls.nummplayerservers = -1;
		cls.pingUpdateSource = AS_MPLAYER;
	}
	else {
		NET_StringToAdr( MASTER_SERVER_NAME, &to );
		cls.numglobalservers = -1;
		cls.pingUpdateSource = AS_GLOBAL;
	}
	to.type = NA_IP;
	to.port = BigShort(PORT_MASTER);

	sprintf( command, "getservers %s", Cmd_Argv(2) );

	// tack on keywords
	buffptr = command + strlen( command );
	count   = Cmd_Argc();
	for (i=3; i<count; i++)
		buffptr += sprintf( buffptr, " %s", Cmd_Argv(i) );

	// if we are a demo, automatically add a "demo" keyword
	if ( Cvar_VariableValue( "fs_restrict" ) ) {
		buffptr += sprintf( buffptr, " demo" );
	}

	NET_OutOfBandPrint( NS_SERVER, to, command );
}