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
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_20__ {TYPE_1__* Server; } ;
struct TYPE_19__ {scalar_t__ Protocol; int ShadowIPv6; scalar_t__ Halt; int /*<<< orphan*/  lock; TYPE_2__* Sock; void* Status; int /*<<< orphan*/  Event; int /*<<< orphan*/  Port; TYPE_6__* Cedar; int /*<<< orphan*/  RandPortId; int /*<<< orphan*/ * NatTGlobalUdpPort; int /*<<< orphan*/  LocalOnly; int /*<<< orphan*/  EnableConditionalAccept; } ;
struct TYPE_18__ {int /*<<< orphan*/  ref; } ;
struct TYPE_17__ {int /*<<< orphan*/  ListenIP; } ;
typedef  TYPE_2__ SOCK ;
typedef  TYPE_3__ LISTENER ;

/* Variables and functions */
 TYPE_2__* Accept (TYPE_2__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV4 ; 
 int IsIPv6Supported () ; 
 scalar_t__ LISTENER_DNS ; 
 scalar_t__ LISTENER_ICMP ; 
 scalar_t__ LISTENER_INPROC ; 
 scalar_t__ LISTENER_REVERSE ; 
 scalar_t__ LISTENER_RUDP ; 
 void* LISTENER_STATUS_LISTENING ; 
 void* LISTENER_STATUS_TRYING ; 
 scalar_t__ LISTENER_TCP ; 
 int LISTEN_RETRY_TIME ; 
 int LISTEN_RETRY_TIME_NOIPV6 ; 
 TYPE_2__* ListenEx2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* ListenEx6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ListenInProc () ; 
 TYPE_2__* ListenRUDPEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* ListenReverse () ; 
 int /*<<< orphan*/  ListenerRUDPRpcRecvProc ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAKE_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 
 int /*<<< orphan*/  SLog (TYPE_6__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TCPAccepted (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPN_RUDP_SVC_NAME ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 

void ListenerTCPMainLoop(LISTENER *r)
{
	SOCK *new_sock;
	SOCK *s;
	// Validate arguments
	if (r == NULL)
	{
		return;
	}

	Debug("ListenerTCPMainLoop Starts.\n");
	r->Status = LISTENER_STATUS_TRYING;

	while (true)
	{
		bool first_failed = true;
		Debug("Status = LISTENER_STATUS_TRYING\n");
		r->Status = LISTENER_STATUS_TRYING;

		// Try to Listen
		while (true)
		{
			UINT interval;
			// Stop flag inspection
			if (r->Halt)
			{
				// Stop
				return;
			}

			s = NULL;

			if (r->Protocol == LISTENER_TCP)
			{
				if (r->ShadowIPv6 == false)
				{
					if (r->Cedar->Server == NULL)
					{
						s = ListenEx2(r->Port, r->LocalOnly, r->EnableConditionalAccept, NULL);
					}
					else
					{
						s = ListenEx2(r->Port, r->LocalOnly, r->EnableConditionalAccept, &r->Cedar->Server->ListenIP);
					}
				}
				else
				{
					s = ListenEx6(r->Port, r->LocalOnly);
				}
			}
			else if (r->Protocol == LISTENER_INPROC)
			{
				s = ListenInProc();
			}
			else if (r->Protocol == LISTENER_RUDP)
			{
				s = ListenRUDPEx(VPN_RUDP_SVC_NAME, NULL, ListenerRUDPRpcRecvProc, NULL, 0, false, false, r->NatTGlobalUdpPort, r->RandPortId, &r->Cedar->Server->ListenIP);
			}
			else if (r->Protocol == LISTENER_ICMP)
			{
				s = ListenRUDPEx(VPN_RUDP_SVC_NAME, NULL, ListenerRUDPRpcRecvProc, NULL, MAKE_SPECIAL_PORT(IP_PROTO_ICMPV4),
					true, false, NULL, 0, &r->Cedar->Server->ListenIP);
			}
			else if (r->Protocol == LISTENER_DNS)
			{
				s = ListenRUDPEx(VPN_RUDP_SVC_NAME, NULL, ListenerRUDPRpcRecvProc, NULL, 53, true, true, NULL, 0, &r->Cedar->Server->ListenIP);
			}
			else if (r->Protocol == LISTENER_REVERSE)
			{
				s = ListenReverse();
			}

			if (s != NULL)
			{
				// Listen success
				AddRef(s->ref);

				Lock(r->lock);
				{
					r->Sock = s;
				}
				Unlock(r->lock);

				if (r->ShadowIPv6 == false && r->Protocol == LISTENER_TCP)
				{
					SLog(r->Cedar, "LS_LISTENER_START_2", r->Port);
				}
				break;
			}

			// Listen failure
			if (first_failed)
			{
				first_failed = false;
				if (r->ShadowIPv6 == false && r->Protocol == LISTENER_TCP)
				{
					SLog(r->Cedar, "LS_LISTENER_START_3", r->Port, LISTEN_RETRY_TIME / 1000);
				}
			}

			interval = LISTEN_RETRY_TIME;

			if (r->ShadowIPv6)
			{
				if (IsIPv6Supported() == false)
				{
					interval = LISTEN_RETRY_TIME_NOIPV6;

					Debug("IPv6 is not supported.\n");
				}
			}

			Wait(r->Event, interval);

			// Stop flag inspection
			if (r->Halt)
			{
				// Stop
				Debug("Listener Halt.\n");
				return;
			}
		}

		r->Status = LISTENER_STATUS_LISTENING;
		Debug("Status = LISTENER_STATUS_LISTENING\n");

		// Stop flag inspection
		if (r->Halt)
		{
			// Stop
			goto STOP;
		}

		// Accept loop
		while (true)
		{
			// Accept
			Debug("Accept()\n");
			new_sock = Accept(s);
			if (new_sock != NULL)
			{
				// Accept success
				Debug("Accepted.\n");
				TCPAccepted(r, new_sock);
				ReleaseSock(new_sock);
			}
			else
			{
STOP:
				Debug("Accept Canceled.\n");
				// Failed to accept (socket is destroyed)
				// Close the listening socket
				Disconnect(s);
				ReleaseSock(s);
				s = NULL;

				Lock(r->lock);
				{
					if (r->Sock != NULL)
					{
						s = r->Sock;
						r->Sock = NULL;
					}
				}
				Unlock(r->lock);

				if (s != NULL)
				{
					ReleaseSock(s);
				}

				s = NULL;

				break;
			}
		}

		// Stop flag inspection
		if (r->Halt)
		{
			// Stop
			Debug("Listener Halt.\n");
			return;
		}
	}
}