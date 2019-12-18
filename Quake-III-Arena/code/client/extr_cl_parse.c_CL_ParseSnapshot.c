#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  newSnap ;
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_20__ {scalar_t__ commandTime; } ;
struct TYPE_15__ {int messageNum; int deltaNum; int parseEntitiesNum; int ping; TYPE_8__ ps; void* valid; int /*<<< orphan*/  areamask; void* snapFlags; int /*<<< orphan*/  serverTime; int /*<<< orphan*/  serverCommandNum; } ;
typedef  TYPE_3__ clSnapshot_t ;
struct TYPE_19__ {int parseEntitiesNum; void* newSnapshots; TYPE_3__ snap; TYPE_3__* snapshots; TYPE_2__* outPackets; } ;
struct TYPE_18__ {int integer; } ;
struct TYPE_13__ {int outgoingSequence; } ;
struct TYPE_17__ {int serverMessageSequence; TYPE_1__ netchan; void* demowaiting; int /*<<< orphan*/  serverCommandSequence; } ;
struct TYPE_16__ {int realtime; } ;
struct TYPE_14__ {scalar_t__ p_serverTime; int p_realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ParsePacketEntities (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int MAX_PARSE_ENTITIES ; 
 void* MSG_ReadByte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ReadData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_ReadDeltaPlayerstate (int /*<<< orphan*/ *,TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  MSG_ReadLong (int /*<<< orphan*/ *) ; 
 int PACKET_BACKUP ; 
 size_t PACKET_MASK ; 
 int /*<<< orphan*/  SHOWNET (int /*<<< orphan*/ *,char*) ; 
 TYPE_7__ cl ; 
 TYPE_6__* cl_shownet ; 
 TYPE_5__ clc ; 
 TYPE_4__ cls ; 
 void* qfalse ; 
 void* qtrue ; 

void CL_ParseSnapshot( msg_t *msg ) {
	int			len;
	clSnapshot_t	*old;
	clSnapshot_t	newSnap;
	int			deltaNum;
	int			oldMessageNum;
	int			i, packetNum;

	// get the reliable sequence acknowledge number
	// NOTE: now sent with all server to client messages
	//clc.reliableAcknowledge = MSG_ReadLong( msg );

	// read in the new snapshot to a temporary buffer
	// we will only copy to cl.snap if it is valid
	Com_Memset (&newSnap, 0, sizeof(newSnap));

	// we will have read any new server commands in this
	// message before we got to svc_snapshot
	newSnap.serverCommandNum = clc.serverCommandSequence;

	newSnap.serverTime = MSG_ReadLong( msg );

	newSnap.messageNum = clc.serverMessageSequence;

	deltaNum = MSG_ReadByte( msg );
	if ( !deltaNum ) {
		newSnap.deltaNum = -1;
	} else {
		newSnap.deltaNum = newSnap.messageNum - deltaNum;
	}
	newSnap.snapFlags = MSG_ReadByte( msg );

	// If the frame is delta compressed from data that we
	// no longer have available, we must suck up the rest of
	// the frame, but not use it, then ask for a non-compressed
	// message 
	if ( newSnap.deltaNum <= 0 ) {
		newSnap.valid = qtrue;		// uncompressed frame
		old = NULL;
		clc.demowaiting = qfalse;	// we can start recording now
	} else {
		old = &cl.snapshots[newSnap.deltaNum & PACKET_MASK];
		if ( !old->valid ) {
			// should never happen
			Com_Printf ("Delta from invalid frame (not supposed to happen!).\n");
		} else if ( old->messageNum != newSnap.deltaNum ) {
			// The frame that the server did the delta from
			// is too old, so we can't reconstruct it properly.
			Com_Printf ("Delta frame too old.\n");
		} else if ( cl.parseEntitiesNum - old->parseEntitiesNum > MAX_PARSE_ENTITIES-128 ) {
			Com_Printf ("Delta parseEntitiesNum too old.\n");
		} else {
			newSnap.valid = qtrue;	// valid delta parse
		}
	}

	// read areamask
	len = MSG_ReadByte( msg );
	MSG_ReadData( msg, &newSnap.areamask, len);

	// read playerinfo
	SHOWNET( msg, "playerstate" );
	if ( old ) {
		MSG_ReadDeltaPlayerstate( msg, &old->ps, &newSnap.ps );
	} else {
		MSG_ReadDeltaPlayerstate( msg, NULL, &newSnap.ps );
	}

	// read packet entities
	SHOWNET( msg, "packet entities" );
	CL_ParsePacketEntities( msg, old, &newSnap );

	// if not valid, dump the entire thing now that it has
	// been properly read
	if ( !newSnap.valid ) {
		return;
	}

	// clear the valid flags of any snapshots between the last
	// received and this one, so if there was a dropped packet
	// it won't look like something valid to delta from next
	// time we wrap around in the buffer
	oldMessageNum = cl.snap.messageNum + 1;

	if ( newSnap.messageNum - oldMessageNum >= PACKET_BACKUP ) {
		oldMessageNum = newSnap.messageNum - ( PACKET_BACKUP - 1 );
	}
	for ( ; oldMessageNum < newSnap.messageNum ; oldMessageNum++ ) {
		cl.snapshots[oldMessageNum & PACKET_MASK].valid = qfalse;
	}

	// copy to the current good spot
	cl.snap = newSnap;
	cl.snap.ping = 999;
	// calculate ping time
	for ( i = 0 ; i < PACKET_BACKUP ; i++ ) {
		packetNum = ( clc.netchan.outgoingSequence - 1 - i ) & PACKET_MASK;
		if ( cl.snap.ps.commandTime >= cl.outPackets[ packetNum ].p_serverTime ) {
			cl.snap.ping = cls.realtime - cl.outPackets[ packetNum ].p_realtime;
			break;
		}
	}
	// save the frame off in the backup array for later delta comparisons
	cl.snapshots[cl.snap.messageNum & PACKET_MASK] = cl.snap;

	if (cl_shownet->integer == 3) {
		Com_Printf( "   snapshot:%i  delta:%i  ping:%i\n", cl.snap.messageNum,
		cl.snap.deltaNum, cl.snap.ping );
	}

	cl.newSnapshots = qtrue;
}