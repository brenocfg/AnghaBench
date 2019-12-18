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
typedef  scalar_t__ UINT64 ;
struct TYPE_15__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_14__ {scalar_t__ Now; int FlushRecvTube; scalar_t__ Status; int Disconnecting; int Aborting; scalar_t__ NextSendEchoRequestTick; scalar_t__ LastRecvTick; int Disconnected; int DisconnectSent; int AbortSent; scalar_t__ AbortReceived; scalar_t__ DisconnectRecved; int /*<<< orphan*/  TubeSend; int /*<<< orphan*/  TubeRecv; int /*<<< orphan*/  Interrupt; int /*<<< orphan*/  RecvQueue; } ;
struct TYPE_13__ {int /*<<< orphan*/  DataSize; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ TUBEDATA ;
typedef  TYPE_2__ SSTP_SERVER ;
typedef  int /*<<< orphan*/  SSTP_PACKET ;
typedef  TYPE_3__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AddInterrupt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeTubeData (TYPE_1__*) ; 
 TYPE_3__* GetNext (int /*<<< orphan*/ ) ; 
 int IsTubeConnected (int /*<<< orphan*/ ) ; 
 int Rand32 () ; 
 int SSTP_ECHO_SEND_INTERVAL_MAX ; 
 int SSTP_ECHO_SEND_INTERVAL_MIN ; 
 int /*<<< orphan*/  SSTP_MSG_CALL_ABORT ; 
 int /*<<< orphan*/  SSTP_MSG_CALL_DISCONNECT ; 
 int /*<<< orphan*/  SSTP_MSG_CALL_DISCONNECT_ACK ; 
 int /*<<< orphan*/  SSTP_MSG_ECHO_REQUEST ; 
 scalar_t__ SSTP_SERVER_STATUS_ESTABLISHED ; 
 scalar_t__ SSTP_TIMEOUT ; 
 int /*<<< orphan*/  SstpAbort (TYPE_2__*) ; 
 int /*<<< orphan*/  SstpDisconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  SstpFreePacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SstpNewControlPacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SstpNewDataPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SstpParsePacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SstpProcessPacket (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SstpSendPacket (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  TubeFlush (int /*<<< orphan*/ ) ; 
 TYPE_1__* TubeRecvAsync (int /*<<< orphan*/ ) ; 

void SstpProcessInterrupt(SSTP_SERVER *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	s->Now = Tick64();

	s->FlushRecvTube = false;

	// Process the received packet
	while (true)
	{
		BLOCK *b = GetNext(s->RecvQueue);
		SSTP_PACKET *p;

		if (b == NULL)
		{
			break;
		}

		p = SstpParsePacket(b->Buf, b->Size);
		if (p == NULL)
		{
			// Disconnect the SSTP since a bad packet received
			SstpAbort(s);
		}
		else
		{
			// Process the received packet
			SstpProcessPacket(s, p);

			SstpFreePacket(p);
		}

		FreeBlock(b);
	}

	if (s->FlushRecvTube)
	{
		TubeFlush(s->TubeRecv);
	}

	// Transmit a packet that the PPP module is trying to send via the SSTP
	while (true)
	{
		TUBEDATA *d = TubeRecvAsync(s->TubeSend);
		SSTP_PACKET *p;
		if (d == NULL)
		{
			break;
		}

		p = SstpNewDataPacket(d->Data, d->DataSize);

		SstpSendPacket(s, p);

		SstpFreePacket(p);

		FreeTubeData(d);
	}

	if (s->Status == SSTP_SERVER_STATUS_ESTABLISHED)
	{
		if (s->Disconnecting == false && s->Aborting == false)
		{
			// Periodic transmission of Echo Request
			if (s->NextSendEchoRequestTick == 0 || s->NextSendEchoRequestTick <= s->Now)
			{
				UINT64 next_interval = (UINT64)(SSTP_ECHO_SEND_INTERVAL_MIN + Rand32() % (SSTP_ECHO_SEND_INTERVAL_MAX - SSTP_ECHO_SEND_INTERVAL_MIN));
				SSTP_PACKET *p;

				s->NextSendEchoRequestTick = s->Now + next_interval;
				AddInterrupt(s->Interrupt, s->NextSendEchoRequestTick);

				p = SstpNewControlPacket(SSTP_MSG_ECHO_REQUEST);

				SstpSendPacket(s, p);

				SstpFreePacket(p);
			}
		}
	}

	if ((s->LastRecvTick + (UINT64)SSTP_TIMEOUT) <= s->Now)
	{
		// Disconnect the SSTP because a timeout occurred
		SstpAbort(s);
		s->Disconnected = true;
	}

	if (IsTubeConnected(s->TubeRecv) == false || IsTubeConnected(s->TubeSend) == false)
	{
		// Disconnect the SSTP since the PPP module is disconnected
		SstpDisconnect(s);
	}

	if (s->Disconnecting)
	{
		// Normal disconnection process
		if (s->DisconnectSent == false)
		{
			// Send a Disconnect
			SSTP_PACKET *ret = SstpNewControlPacket(s->DisconnectRecved ? SSTP_MSG_CALL_DISCONNECT_ACK : SSTP_MSG_CALL_DISCONNECT);

			SstpSendPacket(s, ret);

			SstpFreePacket(ret);

			s->DisconnectSent = true;
		}
	}

	if (s->Aborting)
	{
		// Abnormal disconnection processing
		if (s->AbortSent == false)
		{
			// Send the Abort
			SSTP_PACKET *ret = SstpNewControlPacket(SSTP_MSG_CALL_ABORT);

			SstpSendPacket(s, ret);

			SstpFreePacket(ret);

			s->AbortSent = true;
		}
	}

	if (s->DisconnectSent && s->DisconnectRecved)
	{
		// Disconnect after exchanging the Disconnect each other
		s->Disconnected = true;
	}

	if (s->AbortSent && s->AbortReceived)
	{
		// Disconnect after exchanging the Abort each other
		s->Disconnected = true;
	}
}