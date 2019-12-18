#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  send_buf ;
struct TYPE_11__ {int unsentLength; size_t sock; int /*<<< orphan*/  incomingSequence; scalar_t__ outgoingSequence; int /*<<< orphan*/  remoteAddress; int /*<<< orphan*/  unsentBuffer; int /*<<< orphan*/  unsentFragments; scalar_t__ unsentFragmentStart; } ;
typedef  TYPE_1__ netchan_t ;
struct TYPE_12__ {int /*<<< orphan*/  cursize; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ msg_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_14__ {int /*<<< orphan*/  integer; } ;
struct TYPE_13__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int FRAGMENT_SIZE ; 
 int MAX_MSGLEN ; 
 int MAX_PACKETLEN ; 
 int /*<<< orphan*/  MSG_InitOOB (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_WriteData (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  MSG_WriteLong (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  MSG_WriteShort (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_SendPacket (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t NS_CLIENT ; 
 int /*<<< orphan*/  Netchan_TransmitNextFragment (TYPE_1__*) ; 
 int /*<<< orphan*/ * netsrcString ; 
 TYPE_4__* qport ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__* showpackets ; 

void Netchan_Transmit( netchan_t *chan, int length, const byte *data ) {
	msg_t		send;
	byte		send_buf[MAX_PACKETLEN];

	if ( length > MAX_MSGLEN ) {
		Com_Error( ERR_DROP, "Netchan_Transmit: length = %i", length );
	}
	chan->unsentFragmentStart = 0;

	// fragment large reliable messages
	if ( length >= FRAGMENT_SIZE ) {
		chan->unsentFragments = qtrue;
		chan->unsentLength = length;
		Com_Memcpy( chan->unsentBuffer, data, length );

		// only send the first fragment now
		Netchan_TransmitNextFragment( chan );

		return;
	}

	// write the packet header
	MSG_InitOOB (&send, send_buf, sizeof(send_buf));

	MSG_WriteLong( &send, chan->outgoingSequence );
	chan->outgoingSequence++;

	// send the qport if we are a client
	if ( chan->sock == NS_CLIENT ) {
		MSG_WriteShort( &send, qport->integer );
	}

	MSG_WriteData( &send, data, length );

	// send the datagram
	NET_SendPacket( chan->sock, send.cursize, send.data, chan->remoteAddress );

	if ( showpackets->integer ) {
		Com_Printf( "%s send %4i : s=%i ack=%i\n"
			, netsrcString[ chan->sock ]
			, send.cursize
			, chan->outgoingSequence - 1
			, chan->incomingSequence );
	}
}