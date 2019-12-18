#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  cursize; } ;
typedef  TYPE_3__ msg_t ;
struct TYPE_19__ {scalar_t__ type; } ;
struct TYPE_14__ {size_t outgoingSequence; TYPE_7__ remoteAddress; } ;
struct TYPE_16__ {scalar_t__ nextSnapshotTime; int snapshotMsec; scalar_t__ state; int /*<<< orphan*/ * downloadName; int /*<<< orphan*/  rateDelayed; TYPE_2__ netchan; TYPE_1__* frames; } ;
typedef  TYPE_4__ client_t ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {scalar_t__ time; } ;
struct TYPE_13__ {scalar_t__ messageSent; int messageAcked; int /*<<< orphan*/  messageSize; } ;

/* Variables and functions */
 scalar_t__ CS_ACTIVE ; 
 scalar_t__ NA_LOOPBACK ; 
 size_t PACKET_MASK ; 
 int /*<<< orphan*/  SV_Netchan_Transmit (TYPE_4__*,TYPE_3__*) ; 
 int SV_RateMsec (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ Sys_IsLANAddress (TYPE_7__) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_6__* sv_lanForceRate ; 
 TYPE_5__ svs ; 

void SV_SendMessageToClient( msg_t *msg, client_t *client ) {
	int			rateMsec;

	// record information about the message
	client->frames[client->netchan.outgoingSequence & PACKET_MASK].messageSize = msg->cursize;
	client->frames[client->netchan.outgoingSequence & PACKET_MASK].messageSent = svs.time;
	client->frames[client->netchan.outgoingSequence & PACKET_MASK].messageAcked = -1;

	// send the datagram
	SV_Netchan_Transmit( client, msg );	//msg->cursize, msg->data );

	// set nextSnapshotTime based on rate and requested number of updates

	// local clients get snapshots every frame
	// TTimo - https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=491
	// added sv_lanForceRate check
	if ( client->netchan.remoteAddress.type == NA_LOOPBACK || (sv_lanForceRate->integer && Sys_IsLANAddress (client->netchan.remoteAddress)) ) {
		client->nextSnapshotTime = svs.time - 1;
		return;
	}
	
	// normal rate / snapshotMsec calculation
	rateMsec = SV_RateMsec( client, msg->cursize );

	if ( rateMsec < client->snapshotMsec ) {
		// never send more packets than this, no matter what the rate is at
		rateMsec = client->snapshotMsec;
		client->rateDelayed = qfalse;
	} else {
		client->rateDelayed = qtrue;
	}

	client->nextSnapshotTime = svs.time + rateMsec;

	// don't pile up empty snapshots while connecting
	if ( client->state != CS_ACTIVE ) {
		// a gigantic connection message may have already put the nextSnapshotTime
		// more than a second away, so don't shorten it
		// do shorten if client is downloading
		if ( !*client->downloadName && client->nextSnapshotTime < svs.time + 1000 ) {
			client->nextSnapshotTime = svs.time + 1000;
		}
	}
}