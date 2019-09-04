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
typedef  void* UINT ;
struct TYPE_24__ {TYPE_4__* TcpSock; TYPE_3__* BulkRecvKey; TYPE_2__* BulkSendKey; int /*<<< orphan*/  YourPort; int /*<<< orphan*/  YourIp; int /*<<< orphan*/  MyPort; scalar_t__ DisconnectFlag; } ;
struct TYPE_23__ {int DoNotSetTargetConnectedSock; int /*<<< orphan*/  Lock; int /*<<< orphan*/  TargetConnectedEvent; int /*<<< orphan*/  SockEvent; TYPE_4__* TargetConnectedSock; TYPE_1__* UdpSock; int /*<<< orphan*/  NewSockConnectEvent; int /*<<< orphan*/  NewSockQueue; scalar_t__ ServerMode; } ;
struct TYPE_22__ {int IpClientAdded; int IsRUDPSocket; TYPE_5__* R_UDP_Stack; void* RUDP_OptimizedMss; TYPE_3__* BulkRecvKey; TYPE_2__* BulkSendKey; int /*<<< orphan*/  RemoteIP; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  LocalPort; int /*<<< orphan*/  LocalIP; } ;
struct TYPE_21__ {int /*<<< orphan*/  Ref; } ;
struct TYPE_20__ {int /*<<< orphan*/  Ref; } ;
struct TYPE_19__ {int /*<<< orphan*/  LocalIP; } ;
typedef  TYPE_4__ SOCK ;
typedef  TYPE_5__ RUDP_STACK ;
typedef  TYPE_6__ RUDP_SESSION ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddIpClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Disconnect (TYPE_4__*) ; 
 int /*<<< orphan*/  InsertQueueWithLock (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int IsLocalHostIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoinSockToSockEvent (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int NewTcpPair (TYPE_4__**,TYPE_4__**) ; 
 void* RUDPCalcBestMssForBulk (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  RUDPDisconnectSession (TYPE_5__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_4__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroIP4 (int /*<<< orphan*/ *) ; 

void RUDPInitSock(RUDP_STACK *r, RUDP_SESSION *se)
{
	SOCK *s1, *s2;
	UINT mss;
	// Validate arguments
	if (r == NULL || se == NULL || se->DisconnectFlag)
	{
		return;
	}

	if (se->TcpSock != NULL)
	{
		// It has already been created
		return;
	}

	// Creating a TCP socket pair
	if (NewTcpPair(&s1, &s2) == false)
	{
		// Failed to create. Disconnect the session
		RUDPDisconnectSession(r, se, false);
		return;
	}

	// Calculate the optimal MSS
	mss = RUDPCalcBestMssForBulk(r, se);

	if (r->ServerMode)
	{
		// Server mode
		se->TcpSock = s2;

		JoinSockToSockEvent(s2, r->SockEvent);

		// Update the end point information of the socket s1
		ZeroIP4(&s1->LocalIP);
		s1->LocalPort = se->MyPort;
		Copy(&s1->RemoteIP, &se->YourIp, sizeof(IP));
		s1->RemotePort = se->YourPort;
		if (IsLocalHostIP(&s1->RemoteIP) == false)
		{
			AddIpClient(&s1->RemoteIP);
			s1->IpClientAdded = true;
		}
		s1->IsRUDPSocket = true;

		s1->BulkSendKey = se->BulkSendKey;
		s1->BulkRecvKey = se->BulkRecvKey;

		AddRef(s1->BulkSendKey->Ref);
		AddRef(s1->BulkRecvKey->Ref);

		s1->RUDP_OptimizedMss = mss;

		// Enqueue the newly created socket, and set the event
		InsertQueueWithLock(r->NewSockQueue, s1);
		Set(r->NewSockConnectEvent);
	}
	else
	{
		// Client mode
		Lock(r->Lock);
		{
			if (r->TargetConnectedSock == NULL && r->DoNotSetTargetConnectedSock == false)
			{
				// Update the end point information of the socket s2
				Copy(&s2->LocalIP, &r->UdpSock->LocalIP, sizeof(IP));
				s2->LocalPort = se->MyPort;
				Copy(&s2->RemoteIP, &se->YourIp, sizeof(IP));
				s2->RemotePort = se->YourPort;
				if (IsLocalHostIP(&s2->RemoteIP) == false)
				{
					AddIpClient(&s2->RemoteIP);
					s2->IpClientAdded = true;
				}
				s2->IsRUDPSocket = true;

				s2->BulkSendKey = se->BulkSendKey;
				s2->BulkRecvKey = se->BulkRecvKey;

				AddRef(s2->BulkSendKey->Ref);
				AddRef(s2->BulkRecvKey->Ref);

				s2->RUDP_OptimizedMss = mss;

				// Register the socket to the RUDP stack
				r->TargetConnectedSock = s2;
				s2->R_UDP_Stack = r;
				se->TcpSock = s1;

				JoinSockToSockEvent(s1, r->SockEvent);

				// Set the event to be set when the connection is successful
				Set(r->TargetConnectedEvent);
			}
			else
			{
				Disconnect(s1);
				Disconnect(s2);
				ReleaseSock(s1);
				ReleaseSock(s2);
			}
		}
		Unlock(r->Lock);
	}
}