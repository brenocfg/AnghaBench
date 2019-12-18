#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UDP ;
struct TYPE_20__ {int /*<<< orphan*/  BufferQueue; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/ * s; } ;
struct TYPE_19__ {scalar_t__ Protocol; int ServerMode; TYPE_6__* Udp; TYPE_12__* Session; int /*<<< orphan*/  Cedar; TYPE_4__* FirstSock; TYPE_4__* TubeSock; scalar_t__ IsInProc; TYPE_3__* Tcp; } ;
struct TYPE_18__ {int /*<<< orphan*/  RemoteIP; int /*<<< orphan*/  ref; } ;
struct TYPE_17__ {int /*<<< orphan*/  TcpSockList; } ;
struct TYPE_16__ {scalar_t__ DisconnectTick; } ;
struct TYPE_15__ {int ConnectionDisconnectSpan; int /*<<< orphan*/  PortUDP; } ;
struct TYPE_14__ {TYPE_1__* ClientOption; } ;
typedef  TYPE_2__ TCPSOCK ;
typedef  TYPE_3__ TCP ;
typedef  TYPE_4__ SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_5__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddUDPEntry (int /*<<< orphan*/ ,TYPE_12__*) ; 
 scalar_t__ CONNECTION_TCP ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Disconnect (TYPE_4__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewQueue () ; 
 TYPE_2__* NewTcpSock (TYPE_4__*) ; 
 int /*<<< orphan*/ * NewUDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_4__*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_6__* ZeroMalloc (int) ; 

void StartTunnelingMode(CONNECTION *c)
{
	SOCK *s;
	TCP *tcp;
	TCPSOCK *ts;
	IP ip;
	UINT port;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	tcp = c->Tcp;

	// Protocol
	if (c->Protocol == CONNECTION_TCP)
	{
		// TCP
		s = c->FirstSock;

		if (c->IsInProc)
		{
			AddRef(s->ref);
			c->TubeSock = s;
		}

		ts = NewTcpSock(s);

		if (c->ServerMode == false)
		{
			if (c->Session->ClientOption->ConnectionDisconnectSpan != 0)
			{
				ts->DisconnectTick = Tick64() + c->Session->ClientOption->ConnectionDisconnectSpan * (UINT64)1000;
			}
		}

		LockList(tcp->TcpSockList);
		{
			Add(tcp->TcpSockList, ts);
		}
		UnlockList(tcp->TcpSockList);
		ReleaseSock(s);
		c->FirstSock = NULL;
	}
	else
	{
		// UDP
		s = c->FirstSock;
		Copy(&ip, &s->RemoteIP, sizeof(IP));
		// May disconnect TCP connection at this point
		c->FirstSock = NULL;
		Disconnect(s);
		ReleaseSock(s);

		// Initialization of UDP structure
		c->Udp = ZeroMalloc(sizeof(UDP));

		if (c->ServerMode)
		{
			// Server mode
			// Add an UDP Entry
			AddUDPEntry(c->Cedar, c->Session);
			c->Udp->s = NULL;
		}
		else
		{
			port = c->Session->ClientOption->PortUDP;
			// Client mode
			c->Udp->s = NewUDP(0);
			// Write the IP address and port number
			Copy(&c->Udp->ip, &ip, sizeof(IP));
			c->Udp->port = port;
		}

		// Queue
		c->Udp->BufferQueue = NewQueue();
	}
}