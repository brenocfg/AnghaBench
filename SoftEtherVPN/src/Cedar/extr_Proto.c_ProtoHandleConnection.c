#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_24__ {TYPE_1__* Server; } ;
struct TYPE_23__ {TYPE_4__* impl; } ;
struct TYPE_22__ {int (* SupportedModes ) () ;int (* Init ) (void**,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int (* ProcessData ) (void*,TYPE_2__*,int /*<<< orphan*/ *) ;int (* IsOk ) (void*) ;scalar_t__ (* EstablishedSessions ) (void*) ;int /*<<< orphan*/  (* Free ) (void*) ;int /*<<< orphan*/  (* BufferLimit ) (void*,int) ;int /*<<< orphan*/  (* Name ) () ;} ;
struct TYPE_21__ {int /*<<< orphan*/  LocalPort; int /*<<< orphan*/  LocalIP; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteIP; } ;
struct TYPE_20__ {int /*<<< orphan*/  Data; } ;
struct TYPE_19__ {int DisableOpenVPNServer; } ;
typedef  TYPE_2__ TCP_RAW_DATA ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_3__ SOCK ;
typedef  TYPE_4__ PROTO_IMPL ;
typedef  TYPE_5__ PROTO ;
typedef  int /*<<< orphan*/  INTERRUPT_MANAGER ;
typedef  int /*<<< orphan*/  FIFO ;
typedef  TYPE_6__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  FifoPtr (int /*<<< orphan*/ *) ; 
 int FifoSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeInterruptManager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeTcpRawData (TYPE_2__*) ; 
 scalar_t__ GetNextIntervalForInterrupt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoinSockToSockEvent (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int MAX_BUFFERING_PACKET_SIZE ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewFifoFast () ; 
 int /*<<< orphan*/ * NewInterruptManager () ; 
 int /*<<< orphan*/ * NewSockEvent () ; 
 TYPE_2__* NewTcpRawData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OPENVPN_NEW_SESSION_DEADLINE_TIMEOUT ; 
 int PROTO_MODE_TCP ; 
 int /*<<< orphan*/  PROTO_TCP_BUFFER_SIZE ; 
 TYPE_5__* ProtoDetect (TYPE_3__*) ; 
 int /*<<< orphan*/  ReadFifo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__ const) ; 
 scalar_t__ Recv (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReleaseFifo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ const SOCK_LATER ; 
 scalar_t__ Send (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetTimeout (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TIMEOUT_INFINITE ; 
 scalar_t__ const Tick64 () ; 
 int /*<<< orphan*/  UDPLISTENER_WAIT_INTERVAL ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WriteFifo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__ const) ; 
 int /*<<< orphan*/  stub1 () ; 
 int stub2 () ; 
 int stub3 (void**,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 () ; 
 int stub5 (void*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (void*,int) ; 
 int stub7 (void*) ; 
 scalar_t__ stub8 (void*) ; 
 int /*<<< orphan*/  stub9 (void*) ; 

bool ProtoHandleConnection(CEDAR *cedar, SOCK *sock)
{
	void *impl_data;
	const PROTO_IMPL *impl;
	const PROTO *proto;

	UCHAR *buf;
	TCP_RAW_DATA *recv_raw_data;
	FIFO *send_fifo;
	INTERRUPT_MANAGER *im;
	SOCK_EVENT *se;

	const UINT64 giveup = Tick64() + (UINT64)OPENVPN_NEW_SESSION_DEADLINE_TIMEOUT;

	if (cedar == NULL || sock == NULL)
	{
		return false;
	}

	proto = ProtoDetect(sock);

	if (proto == NULL)
	{
		Debug("ProtoHandleConnection(): unrecognized protocol\n");
		return false;
	}

	impl = proto->impl;

	if (StrCmp(impl->Name(), "OpenVPN") == 0 && cedar->Server->DisableOpenVPNServer == true)
	{
		Debug("ProtoHandleConnection(): OpenVPN detected, but it's disabled\n");
		return false;
	}

	if ((impl->SupportedModes() & PROTO_MODE_TCP) == false)
	{
		return false;
	}

	im = NewInterruptManager();
	se = NewSockEvent();

	if (impl->Init != NULL && impl->Init(&impl_data, cedar, im, se) == false)
	{
		Debug("ProtoHandleConnection(): failed to initialize %s\n", impl->Name());
		FreeInterruptManager(im);
		ReleaseSockEvent(se);
		return false;
	}

	SetTimeout(sock, TIMEOUT_INFINITE);
	JoinSockToSockEvent(sock, se);

	recv_raw_data = NewTcpRawData(&sock->RemoteIP, sock->RemotePort, &sock->LocalIP, sock->LocalPort);
	send_fifo = NewFifoFast();

	buf = Malloc(PROTO_TCP_BUFFER_SIZE);

	Debug("ProtoHandleConnection(): entering main loop\n");

	// Receive data from the TCP socket
	while (true)
	{
		UINT next_interval;
		bool stop = false;

		while (true)
		{
			const UINT ret = Recv(sock, buf, PROTO_TCP_BUFFER_SIZE, false);

			if (ret == SOCK_LATER)
			{
				// No more data to read
				break;
			}
			else if (ret == 0)
			{
				// Disconnected
				stop = true;
				break;
			}
			else
			{
				// Write the received data into the FIFO
				WriteFifo(recv_raw_data->Data, buf, ret);
			}
		}

		if (impl->ProcessData(impl_data, recv_raw_data, send_fifo) == false)
		{
			stop = true;
		}

		// Send data to the TCP socket
		while (FifoSize(send_fifo) >= 1)
		{
			const UINT ret = Send(sock, FifoPtr(send_fifo), FifoSize(send_fifo), false);

			if (ret == SOCK_LATER)
			{
				// Can not write anymore
				break;
			}
			else if (ret == 0)
			{
				// Disconnected
				stop = true;
				break;
			}
			else
			{
				// Remove data that has been sent from the FIFO
				ReadFifo(send_fifo, NULL, ret);
			}
		}

		impl->BufferLimit(impl_data, FifoSize(send_fifo) > MAX_BUFFERING_PACKET_SIZE);

		if (impl->IsOk(impl_data) == false)
		{
			if (impl->EstablishedSessions(impl_data) == 0)
			{
				if (Tick64() >= giveup)
				{
					Debug("ProtoHandleConnection(): I waited too much for the session to start, I give up!\n");
					stop = true;
				}
			}
			else
			{
				Debug("ProtoHandleConnection(): implementation not OK, stopping the server\n");
				stop = true;
			}
		}

		if (stop)
		{
			// Error or disconnection occurs
			Debug("ProtoHandleConnection(): breaking main loop\n");
			break;
		}

		// Wait until the next event occurs
		next_interval = GetNextIntervalForInterrupt(im);
		next_interval = MIN(next_interval, UDPLISTENER_WAIT_INTERVAL);
		WaitSockEvent(se, next_interval);
	}

	impl->Free(impl_data);

	FreeInterruptManager(im);
	ReleaseSockEvent(se);
	FreeTcpRawData(recv_raw_data);
	ReleaseFifo(send_fifo);
	Free(buf);

	return true;
}