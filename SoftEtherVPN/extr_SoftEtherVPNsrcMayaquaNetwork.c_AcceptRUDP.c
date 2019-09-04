#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Protocol; int /*<<< orphan*/  NewSockConnectEvent; int /*<<< orphan*/  NewSockQueue; } ;
struct TYPE_6__ {scalar_t__ Type; int ListenMode; int /*<<< orphan*/  UnderlayProtocol; scalar_t__ CancelAccept; scalar_t__ Disconnecting; TYPE_2__* R_UDP_Stack; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ RUDP_STACK ;

/* Variables and functions */
 TYPE_1__* GetNextWithLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
#define  RUDP_PROTOCOL_DNS 130 
#define  RUDP_PROTOCOL_ICMP 129 
#define  RUDP_PROTOCOL_UDP 128 
 scalar_t__ SOCK_RUDP_LISTEN ; 
 int /*<<< orphan*/  SOCK_UNDERLAY_DNS ; 
 int /*<<< orphan*/  SOCK_UNDERLAY_ICMP ; 
 int /*<<< orphan*/  SOCK_UNDERLAY_NAT_T ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SOCK *AcceptRUDP(SOCK *s)
{
	// Validate arguments
	if (s == NULL || s->Type != SOCK_RUDP_LISTEN || s->ListenMode == false)
	{
		return NULL;
	}

	while (true)
	{
		RUDP_STACK *r = s->R_UDP_Stack;
		SOCK *ret;

		if (s->Disconnecting || s->CancelAccept)
		{
			return NULL;
		}

		ret = GetNextWithLock(r->NewSockQueue);

		if (ret != NULL)
		{
			switch (r->Protocol)
			{
			case RUDP_PROTOCOL_UDP:
				StrCpy(ret->UnderlayProtocol, sizeof(ret->UnderlayProtocol), SOCK_UNDERLAY_NAT_T);
				break;

			case RUDP_PROTOCOL_DNS:
				StrCpy(ret->UnderlayProtocol, sizeof(ret->UnderlayProtocol), SOCK_UNDERLAY_DNS);
				break;

			case RUDP_PROTOCOL_ICMP:
				StrCpy(ret->UnderlayProtocol, sizeof(ret->UnderlayProtocol), SOCK_UNDERLAY_ICMP);
				break;
			}

			return ret;
		}

		Wait(r->NewSockConnectEvent, INFINITE);
	}
}