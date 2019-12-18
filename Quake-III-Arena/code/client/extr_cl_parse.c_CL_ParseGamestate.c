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
typedef  int /*<<< orphan*/  nullstate ;
typedef  int /*<<< orphan*/  msg_t ;
typedef  int /*<<< orphan*/  entityState_t ;
struct TYPE_4__ {int dataCount; int* stringOffsets; scalar_t__ stringData; } ;
struct TYPE_6__ {int /*<<< orphan*/ * entityBaselines; TYPE_1__ gameState; } ;
struct TYPE_5__ {void* checksumFeed; void* clientNum; void* serverCommandSequence; scalar_t__ connectPacketCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ClearState () ; 
 int /*<<< orphan*/  CL_InitDownloads () ; 
 int /*<<< orphan*/  CL_SystemInfoChanged () ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Com_Memcpy (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Con_Close () ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  FS_ConditionalRestart (void*) ; 
 int /*<<< orphan*/  GENTITYNUM_BITS ; 
 int MAX_CONFIGSTRINGS ; 
 int MAX_GAMESTATE_CHARS ; 
 int MAX_GENTITIES ; 
 char* MSG_ReadBigString (int /*<<< orphan*/ *) ; 
 int MSG_ReadBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MSG_ReadByte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ReadDeltaEntity (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* MSG_ReadLong (int /*<<< orphan*/ *) ; 
 int MSG_ReadShort (int /*<<< orphan*/ *) ; 
 TYPE_3__ cl ; 
 TYPE_2__ clc ; 
 int strlen (char*) ; 
 int svc_EOF ; 
 int svc_baseline ; 
 int svc_configstring ; 

void CL_ParseGamestate( msg_t *msg ) {
	int				i;
	entityState_t	*es;
	int				newnum;
	entityState_t	nullstate;
	int				cmd;
	char			*s;

	Con_Close();

	clc.connectPacketCount = 0;

	// wipe local client state
	CL_ClearState();

	// a gamestate always marks a server command sequence
	clc.serverCommandSequence = MSG_ReadLong( msg );

	// parse all the configstrings and baselines
	cl.gameState.dataCount = 1;	// leave a 0 at the beginning for uninitialized configstrings
	while ( 1 ) {
		cmd = MSG_ReadByte( msg );

		if ( cmd == svc_EOF ) {
			break;
		}
		
		if ( cmd == svc_configstring ) {
			int		len;

			i = MSG_ReadShort( msg );
			if ( i < 0 || i >= MAX_CONFIGSTRINGS ) {
				Com_Error( ERR_DROP, "configstring > MAX_CONFIGSTRINGS" );
			}
			s = MSG_ReadBigString( msg );
			len = strlen( s );

			if ( len + 1 + cl.gameState.dataCount > MAX_GAMESTATE_CHARS ) {
				Com_Error( ERR_DROP, "MAX_GAMESTATE_CHARS exceeded" );
			}

			// append it to the gameState string buffer
			cl.gameState.stringOffsets[ i ] = cl.gameState.dataCount;
			Com_Memcpy( cl.gameState.stringData + cl.gameState.dataCount, s, len + 1 );
			cl.gameState.dataCount += len + 1;
		} else if ( cmd == svc_baseline ) {
			newnum = MSG_ReadBits( msg, GENTITYNUM_BITS );
			if ( newnum < 0 || newnum >= MAX_GENTITIES ) {
				Com_Error( ERR_DROP, "Baseline number out of range: %i", newnum );
			}
			Com_Memset (&nullstate, 0, sizeof(nullstate));
			es = &cl.entityBaselines[ newnum ];
			MSG_ReadDeltaEntity( msg, &nullstate, es, newnum );
		} else {
			Com_Error( ERR_DROP, "CL_ParseGamestate: bad command byte" );
		}
	}

	clc.clientNum = MSG_ReadLong(msg);
	// read the checksum feed
	clc.checksumFeed = MSG_ReadLong( msg );

	// parse serverId and other cvars
	CL_SystemInfoChanged();

	// reinitialize the filesystem if the game directory has changed
  FS_ConditionalRestart( clc.checksumFeed );

	// This used to call CL_StartHunkUsers, but now we enter the download state before loading the
	// cgame
	CL_InitDownloads();

	// make sure the game starts
	Cvar_Set( "cl_paused", "0" );
}