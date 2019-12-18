#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int NextSessionId; int /*<<< orphan*/  Dh; int /*<<< orphan*/  Now; void* SendPacketList; void* RecvPacketList; int /*<<< orphan*/  SessionList; int /*<<< orphan*/ * SockEvent; int /*<<< orphan*/ * Interrupt; int /*<<< orphan*/ * Cedar; } ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_1__ OPENVPN_SERVER ;
typedef  int /*<<< orphan*/  INTERRUPT_MANAGER ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  DH_PARAM_BITS_DEFAULT ; 
 int /*<<< orphan*/  DhNewFromBits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 void* NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OvsCompareSessionList ; 
 int /*<<< orphan*/  OvsLog (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Tick64 () ; 
 TYPE_1__* ZeroMalloc (int) ; 

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
	s->Interrupt = interrupt;
	s->SockEvent = sock_event;

	s->SessionList = NewList(OvsCompareSessionList);
	s->RecvPacketList = NewListFast(NULL);
	s->SendPacketList = NewListFast(NULL);

	s->Now = Tick64();

	s->NextSessionId = 1;

	OvsLog(s, NULL, NULL, "LO_START");

	s->Dh = DhNewFromBits(DH_PARAM_BITS_DEFAULT);

	return s;
}