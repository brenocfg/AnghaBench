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
struct TYPE_3__ {int /*<<< orphan*/  Event; int /*<<< orphan*/  PortList; } ;
typedef  TYPE_1__ UDPLISTENER ;

/* Variables and functions */
 int /*<<< orphan*/  DelInt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void DeletePortFromUdpListener(UDPLISTENER *u, UINT port)
{
	// Validate arguments
	if (u == NULL || port == 0)
	{
		return;
	}

	LockList(u->PortList);
	{
		DelInt(u->PortList, port);
	}
	UnlockList(u->PortList);

	SetSockEvent(u->Event);
}