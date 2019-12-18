#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ cursize; scalar_t__ readcount; } ;
typedef  TYPE_1__ msg_t ;
struct TYPE_15__ {int integer; } ;
struct TYPE_14__ {scalar_t__ reliableAcknowledge; scalar_t__ reliableSequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ParseCommandString (TYPE_1__*) ; 
 int /*<<< orphan*/  CL_ParseDownload (TYPE_1__*) ; 
 int /*<<< orphan*/  CL_ParseGamestate (TYPE_1__*) ; 
 int /*<<< orphan*/  CL_ParseSnapshot (TYPE_1__*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 scalar_t__ MAX_RELIABLE_COMMANDS ; 
 int /*<<< orphan*/  MSG_Bitstream (TYPE_1__*) ; 
 int MSG_ReadByte (TYPE_1__*) ; 
 scalar_t__ MSG_ReadLong (TYPE_1__*) ; 
 int /*<<< orphan*/  SHOWNET (TYPE_1__*,char*) ; 
 TYPE_3__* cl_shownet ; 
 TYPE_2__ clc ; 
 int svc_EOF ; 
#define  svc_download 132 
#define  svc_gamestate 131 
#define  svc_nop 130 
#define  svc_serverCommand 129 
#define  svc_snapshot 128 
 char** svc_strings ; 

void CL_ParseServerMessage( msg_t *msg ) {
	int			cmd;

	if ( cl_shownet->integer == 1 ) {
		Com_Printf ("%i ",msg->cursize);
	} else if ( cl_shownet->integer >= 2 ) {
		Com_Printf ("------------------\n");
	}

	MSG_Bitstream(msg);

	// get the reliable sequence acknowledge number
	clc.reliableAcknowledge = MSG_ReadLong( msg );
	// 
	if ( clc.reliableAcknowledge < clc.reliableSequence - MAX_RELIABLE_COMMANDS ) {
		clc.reliableAcknowledge = clc.reliableSequence;
	}

	//
	// parse the message
	//
	while ( 1 ) {
		if ( msg->readcount > msg->cursize ) {
			Com_Error (ERR_DROP,"CL_ParseServerMessage: read past end of server message");
			break;
		}

		cmd = MSG_ReadByte( msg );

		if ( cmd == svc_EOF) {
			SHOWNET( msg, "END OF MESSAGE" );
			break;
		}

		if ( cl_shownet->integer >= 2 ) {
			if ( !svc_strings[cmd] ) {
				Com_Printf( "%3i:BAD CMD %i\n", msg->readcount-1, cmd );
			} else {
				SHOWNET( msg, svc_strings[cmd] );
			}
		}
	
	// other commands
		switch ( cmd ) {
		default:
			Com_Error (ERR_DROP,"CL_ParseServerMessage: Illegible server message\n");
			break;			
		case svc_nop:
			break;
		case svc_serverCommand:
			CL_ParseCommandString( msg );
			break;
		case svc_gamestate:
			CL_ParseGamestate( msg );
			break;
		case svc_snapshot:
			CL_ParseSnapshot( msg );
			break;
		case svc_download:
			CL_ParseDownload( msg );
			break;
		}
	}
}