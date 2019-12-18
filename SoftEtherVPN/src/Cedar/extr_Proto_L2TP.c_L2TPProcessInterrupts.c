#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_55__   TYPE_9__ ;
typedef  struct TYPE_54__   TYPE_8__ ;
typedef  struct TYPE_53__   TYPE_7__ ;
typedef  struct TYPE_52__   TYPE_6__ ;
typedef  struct TYPE_51__   TYPE_5__ ;
typedef  struct TYPE_50__   TYPE_3__ ;
typedef  struct TYPE_49__   TYPE_39__ ;
typedef  struct TYPE_48__   TYPE_2__ ;
typedef  struct TYPE_47__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  error_data ;
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_55__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_54__ {scalar_t__* Buf; int Size; } ;
struct TYPE_53__ {int /*<<< orphan*/  Ns; int /*<<< orphan*/  TunnelId; int /*<<< orphan*/ * AvpList; } ;
struct TYPE_52__ {scalar_t__ NextSendTick; int /*<<< orphan*/  Buf; } ;
struct TYPE_51__ {int Halting; scalar_t__ Now; int HaltCompleted; int /*<<< orphan*/  ThreadList; int /*<<< orphan*/ * IkeServer; int /*<<< orphan*/  HaltCompletedEvent; int /*<<< orphan*/ * TunnelList; int /*<<< orphan*/  FlushList; scalar_t__ Halt; } ;
struct TYPE_50__ {scalar_t__ LastRecvTick; int Timedout; int TunnelId2; int Established; scalar_t__ LastHelloSent; int IsV3; int Disconnecting; int SessionId2; scalar_t__ DisconnectTimeout; int StateChanged; int /*<<< orphan*/  NextNs; int /*<<< orphan*/  TunnelId1; int /*<<< orphan*/ * SendQueue; int /*<<< orphan*/ * SessionList; scalar_t__ IsCiscoV3; scalar_t__ WantToDisconnect; int /*<<< orphan*/  SessionId1; TYPE_1__* TubeRecv; TYPE_39__* EtherIP; int /*<<< orphan*/  TubeSend; scalar_t__ HasThread; } ;
struct TYPE_49__ {int /*<<< orphan*/ * SendPacketList; } ;
struct TYPE_48__ {int /*<<< orphan*/  DataSize; int /*<<< orphan*/  Data; } ;
struct TYPE_47__ {scalar_t__ IntParam1; scalar_t__ IntParam2; } ;
typedef  TYPE_2__ TUBEDATA ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ L2TP_TUNNEL ;
typedef  TYPE_3__ L2TP_SESSION ;
typedef  TYPE_5__ L2TP_SERVER ;
typedef  TYPE_6__ L2TP_QUEUE ;
typedef  TYPE_7__ L2TP_PACKET ;
typedef  TYPE_8__ BUF ;
typedef  TYPE_9__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  BuildL2TPPacketData (TYPE_7__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DisconnectL2TPSession (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  DisconnectL2TPTunnel (TYPE_3__*) ; 
 scalar_t__ Endian16 (int) ; 
 scalar_t__ Endian32 (int) ; 
 int /*<<< orphan*/  EtherIPProcInterrupts (TYPE_39__*) ; 
 int /*<<< orphan*/  FlushTubeFlushList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_9__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_8__*) ; 
 int /*<<< orphan*/  FreeL2TPPacket (TYPE_7__*) ; 
 int /*<<< orphan*/  FreeL2TPQueue (TYPE_6__*) ; 
 int /*<<< orphan*/  FreeL2TPSession (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeL2TPTunnel (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeTubeData (TYPE_2__*) ; 
 int IsTubeConnected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2TPAddInterrupt (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  L2TPSessionManageEtherIPServer (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  L2TPV3_CISCO_AVP_SESSION_ID_LOCAL ; 
 int /*<<< orphan*/  L2TPV3_CISCO_AVP_TUNNEL_ID ; 
 int /*<<< orphan*/  L2TP_AVP_TYPE_ASSIGNED_SESSION ; 
 int /*<<< orphan*/  L2TP_AVP_TYPE_ASSIGNED_TUNNEL ; 
 int /*<<< orphan*/  L2TP_AVP_TYPE_PPP_DISCONNECT_CAUSE ; 
 int /*<<< orphan*/  L2TP_AVP_TYPE_RESULT_CODE ; 
 int /*<<< orphan*/  L2TP_AVP_TYPE_V3_SESSION_ID_LOCAL ; 
 int /*<<< orphan*/  L2TP_AVP_TYPE_V3_TUNNEL_ID ; 
 int /*<<< orphan*/  L2TP_AVP_VENDOR_ID_CISCO ; 
 scalar_t__ L2TP_HELLO_INTERVAL ; 
 scalar_t__ L2TP_HELLO_SUPRESS_MAX_THRETHORD_NUM_SEND_QUEUE ; 
 int /*<<< orphan*/  L2TP_MESSAGE_TYPE_CDN ; 
 int /*<<< orphan*/  L2TP_MESSAGE_TYPE_HELLO ; 
 int /*<<< orphan*/  L2TP_MESSAGE_TYPE_STOPCCN ; 
 scalar_t__ L2TP_PACKET_RESEND_INTERVAL ; 
 scalar_t__ L2TP_TUNNEL_DISCONNECT_TIMEOUT ; 
 scalar_t__ L2TP_TUNNEL_TIMEOUT ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MaintainThreadList (int /*<<< orphan*/ ) ; 
 TYPE_3__* NewAVP (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 TYPE_8__* NewBuf () ; 
 TYPE_7__* NewL2TPControlPacket (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendL2TPControlPacket (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  SendL2TPControlPacketMain (TYPE_5__*,TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  SendL2TPDataPacket (TYPE_5__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopL2TPThread (TYPE_5__*,TYPE_3__*,TYPE_3__*) ; 
 TYPE_2__* TubeRecvAsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_8__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  Zero (scalar_t__*,int) ; 
 TYPE_6__* ZeroMalloc (int) ; 

void L2TPProcessInterrupts(L2TP_SERVER *l2tp)
{
	UINT i, j;
	LIST *delete_tunnel_list = NULL;
	// Validate arguments
	if (l2tp == NULL)
	{
		return;
	}

	if (l2tp->Halt)
	{
		if (l2tp->Halting == false)
		{
			l2tp->Halting = true;

			// Disconnect all tunnels
			for (i = 0;i < LIST_NUM(l2tp->TunnelList);i++)
			{
				L2TP_TUNNEL *t = LIST_DATA(l2tp->TunnelList, i);

				DisconnectL2TPTunnel(t);
			}
		}
	}

	// Flush
	FlushTubeFlushList(l2tp->FlushList);

	// Enumerate all tunnels
	for (i = 0;i < LIST_NUM(l2tp->TunnelList);i++)
	{
		L2TP_TUNNEL *t = LIST_DATA(l2tp->TunnelList, i);
		LIST *delete_session_list = NULL;

		if ((l2tp->Now >= (t->LastRecvTick + (UINT64)L2TP_TUNNEL_TIMEOUT)) && t->Timedout == false)
		{
			// Disconnect the tunnel forcibly if data can not be received for a certain period of time
			t->Timedout = true;

			Debug("L2TP Tunnel %u/%u Timed out.\n", t->TunnelId1, t->TunnelId2);
			DisconnectL2TPTunnel(t);
		}

		if (t->Established && (l2tp->Now >= (t->LastHelloSent + (UINT64)L2TP_HELLO_INTERVAL)))
		{
			if (LIST_NUM(t->SendQueue) <= L2TP_HELLO_SUPRESS_MAX_THRETHORD_NUM_SEND_QUEUE)
			{
				L2TP_PACKET *pp = NewL2TPControlPacket(L2TP_MESSAGE_TYPE_HELLO, t->IsV3);

				// Send a Hello message
				t->LastHelloSent = l2tp->Now;
				//Debug("L2TP Sending Hello %u/%u: tick=%I64u\n", t->TunnelId1, t->TunnelId2, l2tp->Now);

				SendL2TPControlPacket(l2tp, t, 0, pp);

				FreeL2TPPacket(pp);

				L2TPAddInterrupt(l2tp, t->LastHelloSent + (UINT64)L2TP_HELLO_INTERVAL);
			}
		}

		// Enumerate all sessions
		for (j = 0;j < LIST_NUM(t->SessionList);j++)
		{
			L2TP_SESSION *s = LIST_DATA(t->SessionList, j);

			if (s->HasThread)
			{
				// Send packet data
				while (true)
				{
					TUBEDATA *d = TubeRecvAsync(s->TubeSend);

					if (d == NULL)
					{
						break;
					}

					SendL2TPDataPacket(l2tp, t, s, d->Data, d->DataSize);

					FreeTubeData(d);
				}

				if (IsTubeConnected(s->TubeSend) == false)
				{
					// Disconnect the this session because the PPP thread ends
					DisconnectL2TPSession(t, s);
				}
			}

			if (s->IsV3)
			{
				if (s->EtherIP != NULL)
				{
					UINT k;

					L2TPSessionManageEtherIPServer(l2tp, s);

					// Notify an interrupt to the EtherIP module
					EtherIPProcInterrupts(s->EtherIP);

					// Send an EtherIP packet data
					for (k = 0;k < LIST_NUM(s->EtherIP->SendPacketList);k++)
					{
						BLOCK *b = LIST_DATA(s->EtherIP->SendPacketList, k);

						SendL2TPDataPacket(l2tp, t, s, b->Buf, b->Size);

						FreeBlock(b);
					}

					DeleteAll(s->EtherIP->SendPacketList);
				}
			}

			if (s->WantToDisconnect && s->Disconnecting == false)
			{
				// Disconnect the session
				UCHAR error_data[4];
				USHORT us;
				UINT ui;
				UINT ppp_error_1 = 0, ppp_error_2 = 0;

				// Send the session disconnection response
				L2TP_PACKET *pp = NewL2TPControlPacket(L2TP_MESSAGE_TYPE_CDN, s->IsV3);

				if (s->TubeRecv != NULL)
				{
					ppp_error_1 = s->TubeRecv->IntParam1;
					ppp_error_2 = s->TubeRecv->IntParam2;
				}

				// Assigned Session ID
				if (s->IsV3 == false)
				{
					us = Endian16(s->SessionId2);
					Add(pp->AvpList, NewAVP(L2TP_AVP_TYPE_ASSIGNED_SESSION, true, 0,
						&us, sizeof(USHORT)));
				}
				else
				{
					ui = Endian16(s->SessionId2);
					Add(pp->AvpList, NewAVP(L2TP_AVP_TYPE_V3_SESSION_ID_LOCAL, true, 0,
						&ui, sizeof(UINT)));

					if (t->IsCiscoV3)
					{
						Add(pp->AvpList, NewAVP(L2TPV3_CISCO_AVP_SESSION_ID_LOCAL, true, L2TP_AVP_VENDOR_ID_CISCO,
							&ui, sizeof(UINT)));
					}
				}

				// Result-Error Code
				Zero(error_data, sizeof(error_data));
				error_data[1] = 0x03;
				Add(pp->AvpList, NewAVP(L2TP_AVP_TYPE_RESULT_CODE, true, 0,
					error_data, sizeof(error_data)));

				if (ppp_error_1 != 0)
				{
					// PPP Disconnect Cause Code AVP
					BUF *b = NewBuf();
					UCHAR uc;
					USHORT us;

					// Disconnect Code
					us = Endian16(ppp_error_1);
					WriteBuf(b, &us, sizeof(USHORT));

					// Control Protocol Number
					us = Endian16(0xc021);
					WriteBuf(b, &us, sizeof(USHORT));

					// Direction
					uc = (UCHAR)ppp_error_2;
					WriteBuf(b, &uc, sizeof(UCHAR));

					Add(pp->AvpList, NewAVP(L2TP_AVP_TYPE_PPP_DISCONNECT_CAUSE, false, 0,
						b->Buf, b->Size));

					FreeBuf(b);
				}

				SendL2TPControlPacket(l2tp, t, s->SessionId1, pp);

				FreeL2TPPacket(pp);

				// Disconnect the session
				Debug("L2TP Session %u/%u on Tunnel %u/%u Disconnected.\n", s->SessionId1, s->SessionId2,
					t->TunnelId1, t->TunnelId2);
				s->Disconnecting = true;
				s->Established = false;
				s->DisconnectTimeout = l2tp->Now + (UINT64)L2TP_TUNNEL_DISCONNECT_TIMEOUT;

				// Stop the thread
				StopL2TPThread(l2tp, t, s);

				L2TPAddInterrupt(l2tp, s->DisconnectTimeout);
			}

			if (s->Disconnecting && ((l2tp->Now >= s->DisconnectTimeout) || LIST_NUM(t->SendQueue) == 0))
			{
				// Delete the session if synchronization between the client
				// and the server is complete or a time-out occurs
				if (delete_session_list == NULL)
				{
					delete_session_list = NewListFast(NULL);
				}

				Add(delete_session_list, s);
			}
		}

		if (delete_session_list != NULL)
		{
			// Session deletion process
			for (j = 0;j < LIST_NUM(delete_session_list);j++)
			{
				L2TP_SESSION *s = LIST_DATA(delete_session_list, j);

				Debug("L2TP Session %u/%u on Tunnel %u/%u Cleaned up.\n", s->SessionId1, s->SessionId2,
					t->TunnelId1, t->TunnelId2);

				FreeL2TPSession(s);
				Delete(t->SessionList, s);
			}

			ReleaseList(delete_session_list);
		}

		if (t->WantToDisconnect && t->Disconnecting == false)
		{
			// Disconnect the tunnel
			USHORT error_data[4];
			USHORT us;
			UINT ui;
			// Reply the tunnel disconnection response
			L2TP_PACKET *pp = NewL2TPControlPacket(L2TP_MESSAGE_TYPE_STOPCCN, t->IsV3);

			// Assigned Tunnel ID
			if (t->IsV3 == false)
			{
				us = Endian16(t->TunnelId2);
				Add(pp->AvpList, NewAVP(L2TP_AVP_TYPE_ASSIGNED_TUNNEL, true, 0,
					&us, sizeof(USHORT)));
			}
			else
			{
				ui = Endian32(t->TunnelId2);
				Add(pp->AvpList, NewAVP(L2TP_AVP_TYPE_V3_TUNNEL_ID, true, 0,
					&ui, sizeof(UINT)));

				if (t->IsCiscoV3)
				{
					Add(pp->AvpList, NewAVP(L2TPV3_CISCO_AVP_TUNNEL_ID, true, L2TP_AVP_VENDOR_ID_CISCO,
						&ui, sizeof(UINT)));
				}
			}

			// Result-Error Code
			Zero(error_data, sizeof(error_data));
			error_data[1] = 0x06;
			Add(pp->AvpList, NewAVP(L2TP_AVP_TYPE_RESULT_CODE, true, 0,
				error_data, sizeof(error_data)));

			SendL2TPControlPacket(l2tp, t, 0, pp);

			FreeL2TPPacket(pp);

			Debug("L2TP Tunnel %u/%u is Disconnected.\n", t->TunnelId1, t->TunnelId2);
			t->Disconnecting = true;
			t->Established = false;
			t->DisconnectTimeout = l2tp->Now + (UINT64)L2TP_TUNNEL_DISCONNECT_TIMEOUT;
			L2TPAddInterrupt(l2tp, t->DisconnectTimeout);
		}

		if (t->Disconnecting && (((LIST_NUM(t->SendQueue) == 0) && LIST_NUM(t->SessionList) == 0) || (l2tp->Now >= t->DisconnectTimeout)))
		{
			// Delete the tunnel if there is no session in the tunnel when synchronization
			// between the client and the server has been completed or a time-out occurs
			if (delete_tunnel_list == NULL)
			{
				delete_tunnel_list = NewListFast(NULL);
			}

			Add(delete_tunnel_list, t);
		}
	}

	if (delete_tunnel_list != NULL)
	{
		for (i = 0;i < LIST_NUM(delete_tunnel_list);i++)
		{
			L2TP_TUNNEL *t = LIST_DATA(delete_tunnel_list, i);

			Debug("L2TP Tunnel %u/%u Cleaned up.\n", t->TunnelId1, t->TunnelId2);

			FreeL2TPTunnel(t);
			Delete(l2tp->TunnelList, t);
		}

		ReleaseList(delete_tunnel_list);
	}

	// Re-transmit packets
	for (i = 0;i < LIST_NUM(l2tp->TunnelList);i++)
	{
		L2TP_TUNNEL *t = LIST_DATA(l2tp->TunnelList, i);
		UINT j;

		if (LIST_NUM(t->SendQueue) >= 1)
		{
			// Packet to be transmitted exists one or more
			for (j = 0;j < LIST_NUM(t->SendQueue);j++)
			{
				L2TP_QUEUE *q = LIST_DATA(t->SendQueue, j);

				if (l2tp->Now >= q->NextSendTick)
				{
					q->NextSendTick = l2tp->Now + (UINT64)L2TP_PACKET_RESEND_INTERVAL;

					L2TPAddInterrupt(l2tp, q->NextSendTick);

					SendL2TPControlPacketMain(l2tp, t, q);
				}
			}
		}
		else
		{
			// There is no packet to be transmitted, but the state of the tunnel is changed
			if (t->StateChanged)
			{
				// Send a ZLB
				L2TP_QUEUE *q = ZeroMalloc(sizeof(L2TP_QUEUE));
				L2TP_PACKET *pp = NewL2TPControlPacket(0, t->IsV3);

				pp->TunnelId = t->TunnelId1;
				pp->Ns = t->NextNs;
				q->Buf = BuildL2TPPacketData(pp, t);

				SendL2TPControlPacketMain(l2tp, t, q);

				FreeL2TPQueue(q);
				FreeL2TPPacket(pp);
			}
		}

		t->StateChanged = false;
	}

	if (l2tp->Halting)
	{
		if (LIST_NUM(l2tp->TunnelList) == 0)
		{
			// Stop all the L2TP tunnel completed
			if (l2tp->HaltCompleted == false)
			{
				l2tp->HaltCompleted = true;

				Set(l2tp->HaltCompletedEvent);
			}
		}
	}

	// Maintenance the thread list
	if (l2tp->IkeServer == NULL)
	{
		MaintainThreadList(l2tp->ThreadList);
		//Debug("l2tp->ThreadList: %u\n", LIST_NUM(l2tp->ThreadList));
	}
}