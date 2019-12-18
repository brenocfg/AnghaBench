#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {char* stringData; int* stringOffsets; } ;
struct TYPE_6__ {scalar_t__ serverId; TYPE_1__ gameState; } ;
struct TYPE_5__ {scalar_t__ demoplaying; } ;

/* Variables and functions */
 int BIG_INFO_KEY ; 
 int BIG_INFO_VALUE ; 
 size_t CS_SYSTEMINFO ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  Cvar_SetCheatState () ; 
 scalar_t__* Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  FS_PureServerSetLoadedPaks (char const*,char const*) ; 
 int /*<<< orphan*/  FS_PureServerSetReferencedPaks (char const*,char const*) ; 
 int /*<<< orphan*/  Info_NextPair (char const**,char*,char*) ; 
 char const* Info_ValueForKey (char*,char*) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 scalar_t__ atoi (char const*) ; 
 TYPE_3__ cl ; 
 int /*<<< orphan*/  cl_connectedToPureServer ; 
 TYPE_2__ clc ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void CL_SystemInfoChanged( void ) {
	char			*systemInfo;
	const char		*s, *t;
	char			key[BIG_INFO_KEY];
	char			value[BIG_INFO_VALUE];
	qboolean		gameSet;

	systemInfo = cl.gameState.stringData + cl.gameState.stringOffsets[ CS_SYSTEMINFO ];
	// NOTE TTimo:
	// when the serverId changes, any further messages we send to the server will use this new serverId
	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=475
	// in some cases, outdated cp commands might get sent with this news serverId
	cl.serverId = atoi( Info_ValueForKey( systemInfo, "sv_serverid" ) );

	// don't set any vars when playing a demo
	if ( clc.demoplaying ) {
		return;
	}

	s = Info_ValueForKey( systemInfo, "sv_cheats" );
	if ( atoi(s) == 0 ) {
		Cvar_SetCheatState();
	}

	// check pure server string
	s = Info_ValueForKey( systemInfo, "sv_paks" );
	t = Info_ValueForKey( systemInfo, "sv_pakNames" );
	FS_PureServerSetLoadedPaks( s, t );

	s = Info_ValueForKey( systemInfo, "sv_referencedPaks" );
	t = Info_ValueForKey( systemInfo, "sv_referencedPakNames" );
	FS_PureServerSetReferencedPaks( s, t );

	gameSet = qfalse;
	// scan through all the variables in the systeminfo and locally set cvars to match
	s = systemInfo;
	while ( s ) {
		Info_NextPair( &s, key, value );
		if ( !key[0] ) {
			break;
		}
		// ehw!
		if ( !Q_stricmp( key, "fs_game" ) ) {
			gameSet = qtrue;
		}

		Cvar_Set( key, value );
	}
	// if game folder should not be set and it is set at the client side
	if ( !gameSet && *Cvar_VariableString("fs_game") ) {
		Cvar_Set( "fs_game", "" );
	}
	cl_connectedToPureServer = Cvar_VariableValue( "sv_pure" );
}