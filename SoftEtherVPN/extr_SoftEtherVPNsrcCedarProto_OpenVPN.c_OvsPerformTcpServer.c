#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {int Size; scalar_t__* Data; } ;
typedef  TYPE_1__ UDPPACKET ;
typedef  scalar_t__ UCHAR ;
struct TYPE_17__ {int SupressSendPacket; int DisconnectCount; scalar_t__ SessionEstablishedCount; int /*<<< orphan*/ * SessionList; int /*<<< orphan*/ * SendPacketList; } ;
struct TYPE_16__ {scalar_t__ Established; } ;
struct TYPE_15__ {int /*<<< orphan*/  LocalPort; int /*<<< orphan*/  LocalIP; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; } ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_2__ SOCK ;
typedef  TYPE_3__ OPENVPN_SESSION ;
typedef  TYPE_4__ OPENVPN_SERVER ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  INTERRUPT_MANAGER ;
typedef  int /*<<< orphan*/  FIFO ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Clone (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ *) ; 
 scalar_t__ Endian16 (scalar_t__) ; 
 void* FifoPtr (int /*<<< orphan*/ *) ; 
 int FifoSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int /*<<< orphan*/  FreeInterruptManager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeOpenVpnServer (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeUdpPacket (TYPE_1__*) ; 
 scalar_t__ GetNextIntervalForInterrupt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoinSockToSockEvent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_BUFFERING_PACKET_SIZE ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* Malloc (scalar_t__) ; 
 int /*<<< orphan*/ * NewFifoFast () ; 
 int /*<<< orphan*/ * NewInterruptManager () ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_4__* NewOpenVpnServer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewSockEvent () ; 
 int /*<<< orphan*/  NewUdpPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ OPENVPN_NEW_SESSION_DEADLINE_TIMEOUT ; 
 int /*<<< orphan*/  OPENVPN_PROTOCOL_TCP ; 
 scalar_t__ OPENVPN_TCP_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  OvsRecvPacket (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ READ_USHORT (void*) ; 
 scalar_t__ ReadFifo (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 scalar_t__ Recv (TYPE_2__*,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ReleaseFifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCK_LATER ; 
 scalar_t__ Send (TYPE_2__*,void*,int,int) ; 
 int /*<<< orphan*/  SetTimeout (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMEOUT_INFINITE ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UDPLISTENER_WAIT_INTERVAL ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WriteFifo (int /*<<< orphan*/ *,scalar_t__*,int) ; 

bool OvsPerformTcpServer(CEDAR *cedar, SOCK *sock)
{
	OPENVPN_SERVER *s;
	INTERRUPT_MANAGER *im;
	SOCK_EVENT *se;
	FIFO *tcp_recv_fifo;
	FIFO *tcp_send_fifo;
	UINT buf_size = (128 * 1024);
	UCHAR *buf;
	UINT64 giveup_time = Tick64() + (UINT64)OPENVPN_NEW_SESSION_DEADLINE_TIMEOUT;
	LIST *ovs_recv_packet;
	UINT i;
	bool ret = false;
	// Validate arguments
	if (cedar == NULL || sock == NULL)
	{
		return false;
	}

	// Initialize
	buf = Malloc(buf_size);
	im = NewInterruptManager();
	se = NewSockEvent();
	SetTimeout(sock, TIMEOUT_INFINITE);
	JoinSockToSockEvent(sock, se);

	tcp_recv_fifo = NewFifoFast();
	tcp_send_fifo = NewFifoFast();

	ovs_recv_packet = NewListFast(NULL);

	// Create an OpenVPN server
	s = NewOpenVpnServer(cedar, im, se);

	// Main loop
	Debug("Entering OpenVPN TCP Server Main Loop.\n");
	while (true)
	{
		UINT next_interval;
		bool disconnected = false;
		UINT64 now = Tick64();

		// Receive data from a TCP socket
		while (true)
		{
			UINT r = Recv(sock, buf, buf_size, false);
			if (r == SOCK_LATER)
			{
				// Can not read any more
				break;
			}
			else if (r == 0)
			{
				// Disconnected
				disconnected = true;
				break;
			}
			else
			{
				// Read
				WriteFifo(tcp_recv_fifo, buf, r);
			}
		}

		// Separate to a list of datagrams by interpreting the data received from the TCP socket
		while (true)
		{
			UINT r = FifoSize(tcp_recv_fifo);
			if (r >= sizeof(USHORT))
			{
				void *ptr = FifoPtr(tcp_recv_fifo);
				USHORT packet_size = READ_USHORT(ptr);
				if (packet_size != 0 && packet_size <= OPENVPN_TCP_MAX_PACKET_SIZE)
				{
					UINT total_len = (UINT)packet_size + sizeof(USHORT);
					if (r >= total_len)
					{
						if (ReadFifo(tcp_recv_fifo, buf, total_len) != total_len)
						{
							// Mismatch
							disconnected = true;
							break;
						}
						else
						{
							// Read one packet
							UINT payload_len = packet_size;
							UCHAR *payload_ptr = buf + sizeof(USHORT);

							// Pass the packet to the OpenVPN server
							Add(ovs_recv_packet, NewUdpPacket(&sock->RemoteIP, sock->RemotePort,
								&sock->LocalIP, sock->LocalPort,
								Clone(payload_ptr, payload_len), payload_len));
						}
					}
					else
					{
						// Non-arrival
						break;
					}
				}
				else
				{
					// Invalid packet size
					disconnected = true;
					break;
				}
			}
			else
			{
				// Non-arrival
				break;
			}
		}

		// Pass a list of received datagrams to the OpenVPN server
		OvsRecvPacket(s, ovs_recv_packet, OPENVPN_PROTOCOL_TCP);

		// Release the received packet list
		for (i = 0;i < LIST_NUM(ovs_recv_packet);i++)
		{
			UDPPACKET *p = LIST_DATA(ovs_recv_packet, i);

			FreeUdpPacket(p);
		}

		DeleteAll(ovs_recv_packet);

		// Store in the queue by getting a list of the datagrams to be transmitted from the OpenVPN server
		for (i = 0;i < LIST_NUM(s->SendPacketList);i++)
		{
			UDPPACKET *p = LIST_DATA(s->SendPacketList, i);
			// Store the size to the TCP send queue first
			USHORT us = (USHORT)p->Size;
			//Debug(" *** TCP SEND %u\n", us);
			us = Endian16(us);
			WriteFifo(tcp_send_fifo, &us, sizeof(USHORT));

			// Write the data body
			WriteFifo(tcp_send_fifo, p->Data, p->Size);

			// Packet release
			FreeUdpPacket(p);
		}
		DeleteAll(s->SendPacketList);

		// Send data to the TCP socket
		while (FifoSize(tcp_send_fifo) >= 1)
		{
			UINT r = Send(sock, FifoPtr(tcp_send_fifo), FifoSize(tcp_send_fifo), false);

			if (r == SOCK_LATER)
			{
				// Can not write any more
				break;
			}
			else if (r == 0)
			{
				// Disconnected
				disconnected = true;
				break;
			}
			else
			{
				// Wrote out
				ReadFifo(tcp_send_fifo, NULL, r);
			}
		}

		if (FifoSize(tcp_send_fifo) > MAX_BUFFERING_PACKET_SIZE)
		{
			s->SupressSendPacket = true;
		}
		else
		{
			s->SupressSendPacket = false;
		}

		if (s->DisconnectCount >= 1)
		{
			// Session disconnection has occurred on OpenVPN server-side
			disconnected = true;
		}

		if (giveup_time <= now)
		{
			UINT i;
			UINT num_established_sessions = 0;
			for (i = 0;i < LIST_NUM(s->SessionList);i++)
			{
				OPENVPN_SESSION *se = LIST_DATA(s->SessionList, i);

				if (se->Established)
				{
					num_established_sessions++;
				}
			}

			if (num_established_sessions == 0)
			{
				// If the number of sessions is 0 even if wait a certain period of time after the start of server, abort
				disconnected = true;
			}
		}

		if (disconnected)
		{
			// Error or disconnect occurs
			Debug("Breaking OpenVPN TCP Server Main Loop.\n");
			break;
		}

		// Wait until the next event occurs
		next_interval = GetNextIntervalForInterrupt(im);
		next_interval = MIN(next_interval, UDPLISTENER_WAIT_INTERVAL);
		WaitSockEvent(se, next_interval);
	}

	if (s != NULL && s->SessionEstablishedCount != 0)
	{
		ret = true;
	}

	// Release the OpenVPN server
	FreeOpenVpnServer(s);

	// Release object
	FreeInterruptManager(im);
	ReleaseSockEvent(se);
	ReleaseFifo(tcp_recv_fifo);
	ReleaseFifo(tcp_send_fifo);
	Free(buf);

	// Release the received packet list
	for (i = 0;i < LIST_NUM(ovs_recv_packet);i++)
	{
		UDPPACKET *p = LIST_DATA(ovs_recv_packet, i);

		FreeUdpPacket(p);
	}

	ReleaseList(ovs_recv_packet);

	return ret;
}