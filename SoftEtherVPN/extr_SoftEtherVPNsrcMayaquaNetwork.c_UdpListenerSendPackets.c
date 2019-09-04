#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UDPPACKET ;
struct TYPE_3__ {int /*<<< orphan*/  Event; int /*<<< orphan*/  SendPacketList; } ;
typedef  TYPE_1__ UDPLISTENER ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void UdpListenerSendPackets(UDPLISTENER *u, LIST *packet_list)
{
	UINT num = 0;
	// Validate arguments
	if (u == NULL || packet_list == NULL)
	{
		return;
	}

	LockList(u->SendPacketList);
	{
		UINT i;

		num = LIST_NUM(packet_list);

		for (i = 0;i < LIST_NUM(packet_list);i++)
		{
			UDPPACKET *p = LIST_DATA(packet_list, i);

			Add(u->SendPacketList, p);
		}
	}
	UnlockList(u->SendPacketList);

	if (num >= 1)
	{
		SetSockEvent(u->Event);
	}
}