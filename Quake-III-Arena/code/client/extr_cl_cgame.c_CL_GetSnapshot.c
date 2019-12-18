#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numEntities; int /*<<< orphan*/ * entities; int /*<<< orphan*/  ps; int /*<<< orphan*/  areamask; int /*<<< orphan*/  serverTime; int /*<<< orphan*/  ping; int /*<<< orphan*/  serverCommandSequence; int /*<<< orphan*/  snapFlags; } ;
typedef  TYPE_2__ snapshot_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {int parseEntitiesNum; int numEntities; int /*<<< orphan*/  ps; int /*<<< orphan*/  areamask; int /*<<< orphan*/  serverTime; int /*<<< orphan*/  ping; int /*<<< orphan*/  serverCommandNum; int /*<<< orphan*/  snapFlags; int /*<<< orphan*/  valid; } ;
typedef  TYPE_3__ clSnapshot_t ;
struct TYPE_6__ {int messageNum; } ;
struct TYPE_9__ {int parseEntitiesNum; int /*<<< orphan*/ * parseEntities; TYPE_3__* snapshots; TYPE_1__ snap; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,int,int) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_ENTITIES_IN_SNAPSHOT ; 
 int MAX_PARSE_ENTITIES ; 
 int PACKET_BACKUP ; 
 int PACKET_MASK ; 
 TYPE_4__ cl ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean	CL_GetSnapshot( int snapshotNumber, snapshot_t *snapshot ) {
	clSnapshot_t	*clSnap;
	int				i, count;

	if ( snapshotNumber > cl.snap.messageNum ) {
		Com_Error( ERR_DROP, "CL_GetSnapshot: snapshotNumber > cl.snapshot.messageNum" );
	}

	// if the frame has fallen out of the circular buffer, we can't return it
	if ( cl.snap.messageNum - snapshotNumber >= PACKET_BACKUP ) {
		return qfalse;
	}

	// if the frame is not valid, we can't return it
	clSnap = &cl.snapshots[snapshotNumber & PACKET_MASK];
	if ( !clSnap->valid ) {
		return qfalse;
	}

	// if the entities in the frame have fallen out of their
	// circular buffer, we can't return it
	if ( cl.parseEntitiesNum - clSnap->parseEntitiesNum >= MAX_PARSE_ENTITIES ) {
		return qfalse;
	}

	// write the snapshot
	snapshot->snapFlags = clSnap->snapFlags;
	snapshot->serverCommandSequence = clSnap->serverCommandNum;
	snapshot->ping = clSnap->ping;
	snapshot->serverTime = clSnap->serverTime;
	Com_Memcpy( snapshot->areamask, clSnap->areamask, sizeof( snapshot->areamask ) );
	snapshot->ps = clSnap->ps;
	count = clSnap->numEntities;
	if ( count > MAX_ENTITIES_IN_SNAPSHOT ) {
		Com_DPrintf( "CL_GetSnapshot: truncated %i entities to %i\n", count, MAX_ENTITIES_IN_SNAPSHOT );
		count = MAX_ENTITIES_IN_SNAPSHOT;
	}
	snapshot->numEntities = count;
	for ( i = 0 ; i < count ; i++ ) {
		snapshot->entities[i] = 
			cl.parseEntities[ ( clSnap->parseEntitiesNum + i ) & (MAX_PARSE_ENTITIES-1) ];
	}

	// FIXME: configstring changes and server commands!!!

	return qtrue;
}