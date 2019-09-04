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
struct TYPE_3__ {int Halt; int /*<<< orphan*/  AdminListenSock; int /*<<< orphan*/  AdminAcceptThread; int /*<<< orphan*/  HaltEvent; } ;
typedef  TYPE_1__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int WaitThread (int /*<<< orphan*/ ,int) ; 

void NiFreeAdminAccept(NAT *n)
{
	// Validate arguments
	if (n == NULL)
	{
		return;
	}

	n->Halt = true;
	Disconnect(n->AdminListenSock);
	Set(n->HaltEvent);

	while (true)
	{
		if (WaitThread(n->AdminAcceptThread, 1000) == false)
		{
			Disconnect(n->AdminListenSock);
		}
		else
		{
			break;
		}
	}
	ReleaseThread(n->AdminAcceptThread);

	ReleaseSock(n->AdminListenSock);
}