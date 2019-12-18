#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  gameState; } ;
struct TYPE_7__ {int lastPacketSentTime; int /*<<< orphan*/  serverAddress; int /*<<< orphan*/  connectTime; int /*<<< orphan*/ * serverMessage; } ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  servername; scalar_t__ keyCatchers; int /*<<< orphan*/ * updateInfoString; } ;
struct TYPE_5__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 scalar_t__ CA_CHALLENGING ; 
 scalar_t__ CA_CONNECTED ; 
 int /*<<< orphan*/  CL_CheckForResend () ; 
 int /*<<< orphan*/  CL_Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Con_Close () ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  NET_StringToAdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RETRANSMIT_TIMEOUT ; 
 int /*<<< orphan*/  SCR_UpdateScreen () ; 
 TYPE_4__ cl ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 
 TYPE_1__* com_cl_running ; 
 int /*<<< orphan*/  qtrue ; 

void CL_MapLoading( void ) {
	if ( !com_cl_running->integer ) {
		return;
	}

	Con_Close();
	cls.keyCatchers = 0;

	// if we are already connected to the local host, stay connected
	if ( cls.state >= CA_CONNECTED && !Q_stricmp( cls.servername, "localhost" ) ) {
		cls.state = CA_CONNECTED;		// so the connect screen is drawn
		Com_Memset( cls.updateInfoString, 0, sizeof( cls.updateInfoString ) );
		Com_Memset( clc.serverMessage, 0, sizeof( clc.serverMessage ) );
		Com_Memset( &cl.gameState, 0, sizeof( cl.gameState ) );
		clc.lastPacketSentTime = -9999;
		SCR_UpdateScreen();
	} else {
		// clear nextmap so the cinematic shutdown doesn't execute it
		Cvar_Set( "nextmap", "" );
		CL_Disconnect( qtrue );
		Q_strncpyz( cls.servername, "localhost", sizeof(cls.servername) );
		cls.state = CA_CHALLENGING;		// so the connect screen is drawn
		cls.keyCatchers = 0;
		SCR_UpdateScreen();
		clc.connectTime = -RETRANSMIT_TIMEOUT;
		NET_StringToAdr( cls.servername, &clc.serverAddress);
		// we don't need a challenge on the localhost

		CL_CheckForResend();
	}
}