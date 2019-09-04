#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {int NextSessionId; int /*<<< orphan*/  Dh; TYPE_1__* SockEvent; int /*<<< orphan*/  Now; int /*<<< orphan*/  SendPacketList; int /*<<< orphan*/  SessionList; int /*<<< orphan*/ * Interrupt; TYPE_3__* Cedar; } ;
struct TYPE_9__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK_EVENT ;
typedef  TYPE_2__ OPENVPN_SERVER ;
typedef  int /*<<< orphan*/  INTERRUPT_MANAGER ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DH_PARAM_BITS_DEFAULT ; 
 int /*<<< orphan*/  DhNewFromBits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OvsCompareSessionList ; 
 int /*<<< orphan*/  OvsLog (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Tick64 () ; 
 TYPE_2__* ZeroMalloc (int) ; 

OPENVPN_SERVER *NewOpenVpnServer(CEDAR *cedar, INTERRUPT_MANAGER *interrupt, SOCK_EVENT *sock_event)
{
	OPENVPN_SERVER *s;
	// Validate arguments
	if (cedar == NULL)
	{
		return NULL;
	}

	s = ZeroMalloc(sizeof(OPENVPN_SERVER));

	s->Cedar = cedar;

	AddRef(s->Cedar->ref);

	s->Interrupt = interrupt;

	s->SessionList = NewList(OvsCompareSessionList);
	s->SendPacketList = NewListFast(NULL);

	s->Now = Tick64();

	s->NextSessionId = 1;

	if (sock_event != NULL)
	{
		s->SockEvent = sock_event;
		AddRef(s->SockEvent->ref);
	}

	OvsLog(s, NULL, NULL, "LO_START");

	s->Dh = DhNewFromBits(DH_PARAM_BITS_DEFAULT);

	return s;
}