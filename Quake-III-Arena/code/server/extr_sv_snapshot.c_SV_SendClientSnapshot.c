#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ overflowed; int /*<<< orphan*/  allowoverflow; } ;
typedef  TYPE_3__ msg_t ;
typedef  int /*<<< orphan*/  msg_buf ;
struct TYPE_21__ {int /*<<< orphan*/  name; int /*<<< orphan*/  lastClientCommand; TYPE_2__* gentity; } ;
typedef  TYPE_4__ client_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_18__ {int svFlags; } ;
struct TYPE_19__ {TYPE_1__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 
 int MAX_MSGLEN ; 
 int /*<<< orphan*/  MSG_Clear (TYPE_3__*) ; 
 int /*<<< orphan*/  MSG_Init (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_WriteLong (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int SVF_BOT ; 
 int /*<<< orphan*/  SV_BuildClientSnapshot (TYPE_4__*) ; 
 int /*<<< orphan*/  SV_SendMessageToClient (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SV_UpdateServerCommandsToClient (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SV_WriteDownloadToClient (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SV_WriteSnapshotToClient (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  qtrue ; 

void SV_SendClientSnapshot( client_t *client ) {
	byte		msg_buf[MAX_MSGLEN];
	msg_t		msg;

	// build the snapshot
	SV_BuildClientSnapshot( client );

	// bots need to have their snapshots build, but
	// the query them directly without needing to be sent
	if ( client->gentity && client->gentity->r.svFlags & SVF_BOT ) {
		return;
	}

	MSG_Init (&msg, msg_buf, sizeof(msg_buf));
	msg.allowoverflow = qtrue;

	// NOTE, MRE: all server->client messages now acknowledge
	// let the client know which reliable clientCommands we have received
	MSG_WriteLong( &msg, client->lastClientCommand );

	// (re)send any reliable server commands
	SV_UpdateServerCommandsToClient( client, &msg );

	// send over all the relevant entityState_t
	// and the playerState_t
	SV_WriteSnapshotToClient( client, &msg );

	// Add any download data if the client is downloading
	SV_WriteDownloadToClient( client, &msg );

	// check for overflow
	if ( msg.overflowed ) {
		Com_Printf ("WARNING: msg overflowed for %s\n", client->name);
		MSG_Clear (&msg);
	}

	SV_SendMessageToClient( &msg, client );
}