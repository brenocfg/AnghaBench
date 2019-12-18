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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UDPPACKET ;
struct TYPE_5__ {int /*<<< orphan*/  Dh; int /*<<< orphan*/  SendPacketList; int /*<<< orphan*/  RecvPacketList; int /*<<< orphan*/  SessionList; } ;
typedef  int /*<<< orphan*/  OPENVPN_SESSION ;
typedef  TYPE_1__ OPENVPN_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  DhFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeUdpPacket (int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OvsFreeSession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OvsLog (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 

void FreeOpenVpnServer(OPENVPN_SERVER *s)
{
	UINT i;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	OvsLog(s, NULL, NULL, "LO_STOP");

	// Release the sessions list
	for (i = 0; i < LIST_NUM(s->SessionList); ++i)
	{
		OPENVPN_SESSION *se = LIST_DATA(s->SessionList, i);
		OvsFreeSession(se);
	}

	ReleaseList(s->SessionList);

	// Release the incoming packets list
	for (i = 0; i < LIST_NUM(s->RecvPacketList); ++i)
	{
		UDPPACKET *p = LIST_DATA(s->RecvPacketList, i);
		FreeUdpPacket(p);
	}

	ReleaseList(s->RecvPacketList);

	// Release the outgoing packets list
	for (i = 0; i < LIST_NUM(s->SendPacketList); ++i)
	{
		UDPPACKET *p = LIST_DATA(s->SendPacketList, i);
		FreeUdpPacket(p);
	}

	ReleaseList(s->SendPacketList);

	DhFree(s->Dh);

	Free(s);
}