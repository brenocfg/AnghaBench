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
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Event; int /*<<< orphan*/  PortList; } ;
typedef  TYPE_1__ UDPLISTENER ;

/* Variables and functions */
 int /*<<< orphan*/  DelInt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Free (int*) ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int* ZeroMalloc (int) ; 

void DeleteAllPortFromUdpListener(UDPLISTENER *u)
{
	// Validate arguments
	if (u == NULL)
	{
		return;
	}

	LockList(u->PortList);
	{
		UINT num_ports = LIST_NUM(u->PortList);
		UINT *ports = ZeroMalloc(sizeof(UINT) * num_ports);
		UINT i;

		for (i = 0;i < num_ports;i++)
		{
			ports[i] = *((UINT *)(LIST_DATA(u->PortList, i)));
		}

		for (i = 0;i < num_ports;i++)
		{
			UINT port = ports[i];

			DelInt(u->PortList, port);
		}

		Free(ports);
	}
	UnlockList(u->PortList);

	SetSockEvent(u->Event);
}